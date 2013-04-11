<?php

/**
 * @file
 * Save  share data.
 */

define('STATUSES_CONTENT_TYPE', 'statuses');
define('TABLE_FLAG_CONTENT', 'flag_content');
define('TABLE_FIELD_TAGS', 'field_data_field_tags');
define('VOCABULARY_CATEGORIES', 'categories');

/**
 * callback for the page favorite save.
 */
function share_page_add($form_id, $sid = NULL) {
  global $user;
  if ($user->uid != FALSE && (user_access('access content'))) {
    $output = drupal_get_form('share_form_add', $sid);
  }
  else {
    $output = drupal_get_form('user_login');
  }
  return $output;
}

/**
 * share_form_add.
 */
function share_form_add($form, &$form_state, $sid) {
  global $user;
  $path = current_path();
  //set content
  if ($path == PATH_FAVORITE_FORM) {
    $url = (!empty($_GET['url'])) ? check_url($_GET['url']) : '';
    $image = (!empty($_GET['img_src'])) ? check_url($_GET['img_src']) : '';
    $title = (!empty($_GET['win_title'])) ? $_GET['win_title'] : '';

    $encoding = detect_encoding($title);

    if ($encoding != 'UTF-8') {
      $title = iconv($encoding, 'UTF-8', $title);
    }

    //get category for interests
    $category = array('none' => t('Please select the category of interests'));
    $vocabulary = taxonomy_vocabulary_machine_name_load(VOCABULARY_CATEGORIES);
    $tree = '';
    //$tree = taxonomy_get_tree($vocabulary->vid);
    if (!empty($tree)) {
      foreach ($tree as $key => $value) {
        $category[$value->tid] = t($value->name);
      }
    }
    //prepare image
    if (!empty($image)) {
      $filename = array_pop(explode('/', $image));
      $image = file_get_contents($image);
      $file = file_save_data($image, 'public://' . $filename, FILE_EXISTS_RENAME);
      file_usage_add($file, 'share_pin', 'share_pin', $file->fid);
    }
  }
  elseif ($path == 'user/share/' . $sid) {
    $status_object = fbsmp_load_status($sid);
    //dsm($status_object);
    $description = $status_object->message;
    $category = array(0 => t('Add to my Wall'), 1 => t('Add to Favorite'));
    $file = (object) $status_object->attachment->data;
    $url = '';
  }
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => !empty($title) ? $title : '',
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => (!empty($description)) ? $description : '',
  );

  $form['interests'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add interests'),
  );

  $form['category'] = array(
    '#type' => 'select',
    '#title' => '',
    '#options' => $category,
    //'#default_value' => (!empty($category['selected'])) ? $category->fid : '',
    '#states' => array(
      'visible' => array(
        ':input[name="interests"]' => array('checked' => TRUE)
      ),
    ),
  );

  $form['image'] = array(
    '#title' => t('Image'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
    '#default_value' => (!empty($file->fid)) ? $file->fid : '',
    '#upload_location' => 'public://',
  );
  if ($url) {
    $form['source'] = array(
      '#type' => 'textfield',
      '#title' => t('Source'),
      '#default_value' => $url,
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => FALSE,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function detect_encoding($string) {
  static $list = array('utf-8', 'windows-1251');

  foreach ($list as $item) {
    if (!empty($item) && !empty($string)) {
      $sample = iconv($item, $item, $string);
      if (md5($sample) == md5($string)) {
        return $item;
      }
    }
  }
  return NULL;
}

/**
 * Implementation of share_form_add_validate().
 */
function share_form_add_validate($form, &$form_state) {
  if (empty($form_state['values'])) {
    form_error($element, t('These fields is empty.'));
  }
}

/**
 * Implementation of share_form_add_submit()
 */
function share_form_add_submit($form, &$form_state) {
  //dsm($form_state);
  global $user;
  $sid = arg(2);
  $time = REQUEST_TIME;
  $values = array();
  $values = $form_state['values'];
  $current_path = current_path();

  //get fields
  $title = check_plain($values['title']);
  $description = !empty($values['description']) ? check_plain($values['description']) : '';
  $source = ' Sources: ' . check_url($values['source']);

  if (function_exists('statuses_determine_context')) {
    $context = statuses_determine_context();
    $recipient = $context['handler']->find_recipient();
    $type = $context['handler']->type();
  }
  // set $message
  $message = $title . ' ' . $description . ' ' . $source;

  if (!empty($values['image'])) {
    $image = $values['image'];
  }
  $ac_plugin = 'photo';

  if (!empty($recipient) && ($message || $image)) {
    //drupal_write_record('statuses', $object);
    if (function_exists('fbsmp_save_status')) {
      $save_status = fbsmp_save_status($recipient, $type, $message, $ac_plugin, array('fid' => "$image"), NULL, _fbsmp_get_fbss_alerts());
    }
    // set favorite flag
    if (($current_path == PATH_FAVORITE_FORM) || ($current_path == PATH_SHARE_FORM . $sid && $values['category'] == 1)) {
      $fcid = db_insert(TABLE_FLAG_CONTENT)
        ->fields(array(
          'fid' => 2,
          'content_type' => STATUSES_CONTENT_TYPE,
          'content_id' => $save_status->sid,
          'uid' => $user->uid,
          'sid' => 0,
          'timestamp' => REQUEST_TIME,
        ))
        ->execute();
    }
  }
  //set category
  if ($current_path == PATH_FAVORITE_FORM && !empty($values['interests']) && !empty($values['category']) && $values['category'] != 'none') {
    if ($save_status) {
      // Update the count with the new value otherwise.
      $fcat = db_insert(TABLE_FIELD_TAGS)
        ->fields(array(
          'entity_type' => STATUSES_CONTENT_TYPE,
          'bundle' => STATUSES_CONTENT_TYPE,
          'deleted' => 0,
          'entity_id' => $save_status->sid,
          'revision_id' => $save_status->sid,
          'language' => LANGUAGE_NONE,
          'delta' => 0,
          'field_tags_tid' => $values['category'],
        ))
        ->execute();
    }
  }
}