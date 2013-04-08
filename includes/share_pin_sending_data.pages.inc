<?php

/**
 * @file
 * Save  share data.
 */

/**
 * callback for the favorite save.
 */
function share_pin_sending_data_form($form, &$form_state, $uid) {

  drupal_add_css(drupal_get_path('module', 'share_pin') . '/css/share_pin.form.css');
  //add count
  drupal_add_js("(function(){
    var time_for_close = 5;
    return setInterval(function(){
        time_for_close--;
        if(time_for_close == 0) window.close();
        document.getElementsByClassName('timer')[0].innerHTML = '['+time_for_close+'c]';
    },1000); })();", array('type' => 'inline', 'scope' => 'header'));

  $form = array();

  $form['save_massage'] = array(
    '#type' => 'fieldset',
    '#description' => t('Saved'),
    '#title' => t('Sending content to katmary'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['save_massage']['view_link'] = array(
    '#type' => 'submit',
    '#value' => t('View'),
    '#attributes' => array(
      'class' => array('btn_redirect'),
      'onclick' => array('window.opener.location.href = "http://'.$_SERVER["SERVER_NAME"].'/user/'.$uid.'/share-bookmarks"; window.close(); return false;'),
    ),
  );

  $form['save_massage']['close_link'] = array(
    '#type' => 'submit',
    '#value' => t('Close'),
    '#attributes' => array(
      'class' => array('close_timer'),
      'onclick' => array('window.close();return false;'),
    ),
    '#suffix' => '<span class="timer">[5c]</span>',
  );

  return $form;
}