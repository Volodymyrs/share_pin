<?php

/**
 * @file
 * Save  share data.
 */

/**
 * callback for the favorite save.
 */
function test_data_form(){
  $context = statuses_determine_context();
  $recipient = $context['handler']->find_recipient();
  $type = $context['handler']->type();
  $form = drupal_get_form('statuses_box', $recipient, $type);
  return $form;
}


function statuses_box_form($form, &$form_state, $recipient, $type = 'user') {
    global $user;
    //_statuses_use_autogrow();
    if (isset($form_state['statuses'])) {
      $type = $form_state['statuses']['type'];
      $context = statuses_determine_context($type);
      $rid = $form_state['statuses']['recipient'];
      $recipient = $context['handler']->load_recipient($rid);
    }
    else {
      $context = statuses_determine_context($type);
      $rid = $context['handler']->recipient_id($recipient);
    }

    $default = variable_get('statuses_default_text' . ($type == 'user' && $user->uid == $recipient->uid ? '' : '_other'), '');
    $intro = '';
    if (arg(0) == 'statuses' && (arg(1) == 'share' || arg(1) == 'conversation')) {
      // This page is autofocused. We don't want default text there since the user would have to manually remove it.
      $default = '';
    }
    if (isset($_GET['s']) && arg(0) == 'statuses' && arg(1) == 'share') {
      // Other modules might use "s," so only accept it on the share-status page.
      $default = $_GET['s'];
    }
    elseif (isset($_GET['share-status'])) {
      $default = $_GET['share-status'];
    }
    // TODO: Replace with a "true" re-posting system.
    if (isset($_GET['sid']) && is_numeric($_GET['sid'])) {
      $rs = statuses_load($_GET['sid']);
      $sender = user_load($rs->sender);
      if ($sender->uid != $user->uid && $rs->message) {
        $name = '@' . $sender->name;
        // Properly reference tags with word-break characters in them.
        if (preg_match('/.+\b.+/', $sender->name)) {
          $name = '[' . $name . ']';
        }
        $default = str_replace(array('@name', '@message'), array($name, $rs->message), variable_get('statuses_repost', 'Re: @name @message '));
        $intro = '';
      }
    }
    elseif (isset($_GET['rsid']) && is_numeric($_GET['rsid'])) {
      $status = statuses_load($_GET['rsid']);
      if ($status->sid) {
        $sender = user_load($status->sender);
        if ($sender->uid != $user->uid) {
          $name = '@' . $sender->name;
          // Properly reference tags with word-break characters in them.
          if (preg_match('/.+\b.+/', $sender->name)) {
            $name = '[' . $name . ']';
          }
          $default = $name . ' ';
        }
        $intro = t('In response to: !status', array('!status' => statuses_show($status, array('links' => FALSE, 'extras' => FALSE))));
      }
    }

    $path = drupal_get_path('module', 'statuses') . '/resources';
    drupal_add_js($path . '/statuses.js');
    if (variable_get('statuses_enter', 0)) {
      drupal_add_js($path .'/statuses_enter.js');
    }
    drupal_add_js($path . '/statuses_ahah.js', array('scope' => 'footer', 'defer' => TRUE));
    drupal_add_css($path . '/statuses.css');
    // Form elements between ['opendiv'] and ['closediv'] will be refreshed via AHAH on form submission.
    $form['opendiv'] = array(
      '#markup' => '<div id="statuses-replace" class="statuses-form">',
      '#weight' => -50,
    );
    if (!empty($intro)) {
      $form['intro'] = array(
        '#markup' => '<span class="statuses-intro">' . $intro . '</span>',
        '#weight' => -45,
      );
    }
    if (variable_get('statuses_length', 140) > 0) {
      $form['chars'] = array(
        '#markup' => '<span class="statuses-chars">' . t('%chars characters allowed', array('%chars' => variable_get('statuses_length', 140))) . '</span>',
        '#weight' => -41,
      );
    }
    $form['fbss-status'] = array(
      '#type' => 'textarea',
      '#rows' => variable_get('statuses_box_rows', 2),
      '#default_value' => $default,
      '#attributes' => array('class' => array('statuses-text', 'statuses-text-main')),
      '#resizable' => FALSE,
      '#prefix' => '<div class="statuses-textarea-wrapper">',
      '#suffix' => '</div>',
      '#weight' => -40,
    );
    $form['fbss-submit'] = array(
      '#type' => 'submit',
      '#value' => t('Share'),
      '#submit' => array('statuses_box_submit'),
      '#attributes' => array('class' => array('statuses-submit', 'button', 'primary')),
      '#weight' => -25,
    );
    if (variable_get('statuses_ahah', 1)) {
      $form['fbss-submit']['#ajax'] = array(
        'path' => 'statuses/ajax',
        'callback' => 'statuses_save_js',
        'wrapper' => 'statuses-replace',
        'keypress' => TRUE,
      );
    }
    $form['sdefault'] = array(
      '#type' => 'value',
      '#value' => $default,
      '#weight' => -10,
    );
    // Form elements between ['opendiv'] and ['closediv'] will be refreshed via AHAH on form submission.
    $form['closediv'] = array(
      '#markup' => '</div>',
      '#weight' => -1,
    );
    $form['recipient'] = array(
      '#type' => 'value',
      '#value' => $context['handler']->recipient_id($recipient),
      '#weight' => 10,
    );
    $form['type'] = array(
      '#type' => 'value',
      '#value' => $type,
      '#weight' => 10,
    );
    if (arg(0) == 'statuses' && arg(1) == 'share' && !empty($_GET['destination']) && $_GET['destination'] != $_GET['q']) {
      $form['back'] = array(
        '#markup' => l(t('Back'), $_GET['destination'], array('attributes' => array('class' => array('statuses-back')))),
        '#weight' => 20,
      );
    }
    return $form;
  }