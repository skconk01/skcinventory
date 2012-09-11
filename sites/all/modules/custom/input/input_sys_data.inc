<?php

// $Id: input_os_data.inc,v 1.2 2012/08/21 19:38:55 stephen Exp stephen $


/**
 * @file input_sys_data.inc
 *
 *  os data input collection 
 */


/**
 * function called by skc_menu 
 */
  function skc_confuration_file_form($form, &$form_state){
    
   // Required for forms with file inputs.
  $form['#attributes'] = array('enctype' => "multipart/form-data");

  // get access to the user name
  global $user;
  $name = $user->name;

  // get a list of computers used by this user
  $computer_list = invdb_get_computer_list($name);
 
  $lst = array();
  //$lst['0'] = '';
  foreach ($computer_list as $computer){
    if ($computer->sos_name == 'Linux'){
      $idbyos = $computer->hostname . '.html';  // id by your os  L is for linux and expects a html file
    }else{
      $idbyos = $computer->hostname . '.txt';  // id by your os  W or not L is for windows and expects a txt file
    }
    $inv_id = $computer->inv_id;
    $lst[$idbyos] = $computer->hostname;
  }
  

 
  // Added AJAX callback.
  $form['computer_name']['name'] = array(
    '#title' => t('Select the hostame of the system the info file is related to.'),
    '#type' => 'radios',
    '#options' => $lst,
    '#ajax' => array(
      'callback' => 'skc_info_file_ajax_callback',
      'wrapper' => 'skc_info_file_wrapper',
     ),
  );
  
  // Setting an empty element with a wrapper to be populated.
  $form['computer_name']['info_file'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="skc_info_file_wrapper">',
    '#suffix' => '</div>',
  );
  
  // When submitted, check for value of OS, and populate os_verify.
  if (isset($form_state['values']['name'])) { // Fixed this line, was throwing an error in the original video code.
    $form['computer_name']['info_file']['#title'] = t('rename your info file name to ==>  @os and upload', array('@os' => $form_state['values']['name']));
    $form['computer_name']['info_file']['#type'] = 'file';
    // the required attribute did not work here something to check into
    //$form['computer_name']['info_file']['#required'] = TRUE;  
    
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  return $form;
  }//end skc_confuration_file_form


/**
 * AJAX callback for OS verification.
 */
function skc_info_file_ajax_callback($form, $form_state) {
  return $form['computer_name']['info_file'];
}





/**
 * Validation for configuration file form  and yes the methiod name is miss-spelled
 */
function skc_confuration_file_form_validate($form, &$form_state) {

  $stop = 'here';

  $selected_fn = $form_state['values']['name'];
  
  
  $validators = array(
     'file_validate_extensions' => array('html txt'),
     'skc_validate_not_in_filename' => array($selected_fn),
   );


  // look in $_FILES->files->name to find in this case info_file
  //$file = file_save_upload('info_file');
  $file = file_save_upload('info_file', $validators, FALSE, FILE_EXISTS_REPLACE);

  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // Put the temporary file in form_values so we can save it on submit.
      $form_state['values']['info_file'] = $file;
    }
    else {
      form_set_error('info_file', t('The file could not be uploaded.'));
    }
  } else {
    form_set_error('info_file', t('It appears that no file was selected. choose the info file associated with your computer and submit '));
  }
}


/**
 * Implements hook_file_validate().
 *
 * We're testing to see if the string 'test.' exists in the file name.
 */
function skc_file_validate($file) {
  $errors = array();
  if (strpos($file->filename, 'test.') !== FALSE) {
    $errors[] = 'The filename "test" is reserved, please change the filename and try again.';
  }
  return $errors;
}



/**
 * Validation function for file to test that a file does not certain a certain string.
 */
function skc_validate_not_in_filename($file, $selected_fn = 'xxxxxx') {
  
  $stop = 'here';
  $fn = $file->filename;
  
  //$fds = strcmp($string, $fn);
  
  $errors = array();
  if (strcmp($fn, $selected_fn) !== 0) {
    //$errors[] = t('The file name  "%string" ring from your filename and try again.', array('%string' => $selected_fn));
    $errors[] = t("the file name $fn does not match the file namy you were instructed to name your upload file $selected_fn");
  }
  return $errors;
}



/**
 * Submit function for unmanaged file form.
 */
function skc_confuration_file_form_submit($form, &$form_state) {
  
  // Check if a file was uploaded.
  if ($file = $form_state['values']['info_file']) {
    
    // Create the directory if it doesn't exist
    $directory = 'public://inventory/configuration_files';
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    
    // Copy the file over.
    $filename = file_unmanaged_copy($file->uri, $directory, FILE_EXISTS_REPLACE);
    
    drupal_set_message(t("Your file has been uploaded!"));
  }
}
