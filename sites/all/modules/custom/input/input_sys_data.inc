<?php

// $Id: input_os_data.inc,v 1.2 2012/08/21 19:38:55 stephen Exp stephen $


/**
 * @file
 *
 *  os data input collection 
 */


/**
 * function to create os data input form
 *
 */
function input_os_data_1($form, &$form_state) {
  
  global $user;
  
  if(isset($user->name)){
    $name = $user->name;
  }else {
    $form['loginerror'] = array(
        '#type' => 'item',
        '#title' => t('You will need to login to proceed.'),
    );
    return $form;
    
  }
  
    
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('This form will collect the OS  information about your system. <br \>'),
  );

  $form['user'] = array(
      '#title' => t('user'),
      '#type' => 'textfield',
      '#maxlength' => 16,
      '#size' => 16,
      '#required' => TRUE,
      '#default_value' => "$name",
			);

 
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  //-----------------------------------------------------------------------------
  return $form;
}
