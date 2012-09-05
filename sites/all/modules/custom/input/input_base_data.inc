<?php

// $Id: input_base_data.inc,v 1.5 2012/08/23 13:36:23 stephen Exp stephen $


/**
 * @file
 *
 *  base data input collection 
 */


/**
 * function to create base data input form
 *
 */
function input_base_data_1($form, &$form_state) {
  
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
    '#title' => t('This form will collect the base information about your system. <br \>
                   Input the base data for each system you have first.'),
  );

  $form['user'] = array(
      '#title' => t('user'),
      '#type' => 'textfield',
      '#maxlength' => 128,
      '#size' => 30,
      '#required' => TRUE,
      '#default_value' => "$name",
			);

  $form['cubid'] = array(
      '#title' => t('Cub Id'),
      '#type' => 'textfield',
      '#maxlength' => 16,
      '#size' => 16,
      '#required' => TRUE,
			 );

  $form['fixed_asset_tag'] = array(
      '#title' => t('Fixed Asset Tag'),
      '#type' => 'textfield',
      '#maxlength' => 10,
      '#size' => 10,
      '#required' => TRUE,
      '#default_value' => 'F0',
      '#description' => t('Leave as F0 if your system does not have an Fixed Asset Tag'),
  );

  $form['serialnum'] = array(
      '#title' => t('Serial Number'),
      '#type' => 'textfield',
      '#maxlength' => 16,
      '#size' => 16,
      '#description' => t('Only requied for Windows systems, Linux systems will have the serial number in the system info file.'),
      			 );

  $form['hostname'] = array(
      '#title' => t('Host Name'),
      '#type' => 'textfield',
      '#maxlength' => 32,
      '#size' => 32,
      '#description' => t('Your systems hostname'),
      '#required' => TRUE,
       );

 $form['ipaddress'] = array(
      '#title' => t('ipaddress'),
      '#type' => 'textfield',
      '#maxlength' => 16,
      '#size' => 16,
      '#description' => t('Your systems ipaddress'),
     '#required' => TRUE,
       );




  $form['machine_type'] = array(
      '#title' => t('Laptop or Desktop'),
      // '#type' => 'radios',
      '#type' => 'select',
      '#options' => array('L' => t('Laptop'), 'D' => t('Desktop')),
      '#required' => TRUE,
  );
  
  $form['machine_user'] = array(
      '#title' => t('Machine Used For'),
      //'#type' => 'radios',
      '#type' => 'select',
      '#options' => array('J' => t('JobZone'), 'O' => t('OSOS'), 'B' => t('Both')),
      '#required' => TRUE,
  );
  
  $form['machine_task'] = array(
      '#title' => t('Machine Used For Develpment, Business Analyst, Support'),
      //'#type' => 'radios',
      '#type' => 'select',
      '#options' => array('D' => t('Development'),  'B' => t('Business Analyst'), 'S' => t('Support'), 'O' => t('Other'), ),
      '#required' => TRUE,
  );
  


  $date = '1970-01-01';
  $format = 'Y-m-d';
  $form['service_date'] = array(
      '#title' => t('Date put in Service'),
      '#type' => 'date_popup',
      '#default_value' => $date,
      '#date_format' => $format,
      //'#date_year_range' => '-15:+0',
      '#date_year_range' => '-15:0',
      '#description' => t('Please select a date. if not known use 1997. click in the form window for a calender'),
      '#default_value' => "01-01-70",
  );
  
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  //-----------------------------------------------------------------------------
  return $form;
} // end of function input_base_data_1



/**
 * submit function for the input_base_data_1 from
 */
function input_base_data_1_submit($form, &$form_state) {

  $db_table = 'zz_team_inv';
  global $user; // to get access to the name curent user
  $n = $user->name;



  $form['hostname']['#value'];
  $form_input['name'] = $form_state['values']['user']; //name of user
  $form_input['cubid'] = $form_state['values']['cubid'];
  $form_input['fixed_asset_tag'] = $form_state['values']['fixed_asset_tag'];
  $form_input['serial-number'] = $form_state['values']['serialnum'];
  $form_input['hostname'] = $form_state['values']['hostname'];
  $form_input['ipaddress'] = $form_state['values']['ipaddress'];
  $form_input['machine_type'] = $form_state['values']['machine_type']; //L laptop D desktop
  $form_input['machine_user'] = $form_state['values']['machine_user'];
  $form_input['machine_task'] = $form_state['values']['machine_task'];
  $form_input['service_date_eop'] = get_epoch($form_state['values']['service_date']);
  $form_input['service_date_str'] = $form_state['values']['service_date'];
  
  if (module_exists('invdb')) {
    drupal_set_message(t("module exists"));
    if (function_exists('invdb_update_database')) {
      drupal_set_message(t("funciotn exists"));
      invdb_update_database($db_table, $form_input);
    }
  }   


  
  // Display a message upon successful submission.
  drupal_set_message(t('form more form submited there @n', array(@n=>$user->name)));

}//end of input_base_data_1_submit




//----------------------------------------------------------------------------
/**
 * caculate the epoch from the input date and return the epoch
 * @param string    $date
 * @return integer  $ep   date as an epoch value
 */
function get_epoch($date){
  $stop = 'here';
  $ep = strtotime($date);

  return $ep;
}





