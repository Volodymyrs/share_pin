<?php

/**
 * @file
 * Save  share data.
 */

/**
 * callback for the favorite save.
 */
function share_page_add(){
  global $user;
  if ($user->uid != FALSE && (user_access('access content'))) {
    $output = drupal_get_form('share_form_add');
  }
  else{
    $output = drupal_get_form('user_login');
  }
  return $output;
}


function share_form_add($form, &$form_state) {
  global $user;
  $url = (!empty($_GET['url'])) ? check_url($_GET['url']) : '';
  $image = (!empty($_GET['img_src'])) ? check_url($_GET['img_src']) : '';
  $title = (!empty($_GET['win_title'])) ? check_plain($_GET['win_title']) : '';

  //get category for interests
  $category = array('none' => t('Please select the category of interests'));
  $vocabulary = taxonomy_vocabulary_machine_name_load('tags');
  $tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($tree as $key => $value) {
    $category[$value->name] = t($value->name);
  }

  //prepare image
  if (!empty($image)) {
    $filename = array_pop(explode('/', $image));
    $image = file_get_contents($image);
    $file = file_save_data($image, 'public://' . $filename, FILE_EXISTS_RENAME);
    file_usage_add($file, 'share_pin', 'share_pin', $file->fid);
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $title,
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => '',
  );

  $form['interests'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add interests'),
  );

  $form['category'] = array(
    '#type' => 'select',
    '#title' => '',
    '#options' => $category,
    '#default_value' => (!empty($category['selected'])) ? $file->fid : '',
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
    '#default_value' =>  (!empty($file->fid)) ? $file->fid : '',
    '#upload_location' => 'public://',
  );

  $form['source'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#default_value' => $url,
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function share_form_add_validate($form, &$form_state) {}


function share_form_add_submit($form, &$form_state) {
  global $user;
  //dsm($form_state);
  $values = array();
  $values = $form_state['values'];

  $time = REQUEST_TIME;
  if(function_exists('statuses_determine_context')){
    $context = statuses_determine_context();
    $recipient = $context['handler']->find_recipient();  //+
    $type = $context['handler']->type();                 //+
  }
  $description = !empty($values['description']['value']) ? check_plain($values['description']['value']) : '';

  // set $message
  $message = '';
  $message  = check_plain($values['title']);
  $message .=  $description;
  $message .= 'Source:' . check_url($values['source']);
  $image = $values['image'];
  $ac_plugin = 'photo';

  if(!empty($recipient) && ($message || $image)){
    //drupal_write_record('statuses', $object);
    if(function_exists('fbsmp_save_status')){
      $save_status = fbsmp_save_status($recipient, $type, $message, $ac_plugin, array('fid'=>"$image"), NULL, _fbsmp_get_fbss_alerts());
    }
    //todo need to set object
    $fcid = db_insert('flag_content')
      ->fields(array(
        'fid' => 2,
        'content_type' => 'statuses',
        'content_id' => $save_status->sid,
        'uid' => $user->uid,
        'sid' => 0,
        'timestamp' => REQUEST_TIME,
      ))
      ->execute();
  }
  //set category
  if(!empty($values['interests']) && !empty($values['category']) && $values['category'] != 'none'){
    if($save_status){
      // Update the count with the new value otherwise.
      $fcat = db_insert('field_data_field_tags')
        ->fields(array(
          'entity_type' => 'share_element',
          'bundle' => 'share_element',
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