<?php


/**
 * @file
 *
 *  os data input collection 
 */






function input_os_data_1($form, &$form_state, $no_js_use = FALSE) {

global $user;
  $name;
  if(isset($user->name)){
    $name = $user->name;
  }else {
    $form['loginerror'] = array(
        '#type' => 'item',
        '#title' => t('You will need to login to proceed.'),
    );
    return $form;
   }
   


  //$computer_list = drupal_map_assoc( array('bonk', 'chobani', 'tiger', ));

// get a list of computers used by this user
  $computer_list = invdb_get_computer_list($name);


  $lst = array();
  //$lst['0'] = '';
  foreach ($computer_list as $computer){
  
    $inv_id = $computer->inv_id;
    $lst[$inv_id] = $computer->hostname;
  }
  

  // Provide a wrapper around the entire form, since we'll replace the whole
  // thing with each submit.
  $form['#prefix'] = '<div id="wonk-form-wrapper">';
  $form['#suffix'] = '</div>';
  $form['#tree'] = TRUE; // We want to deal with hierarchical form values.


  $form['description'] = array(
    '#markup' => '<div>' . t(
'This example is a step-by-step wizard. wonk style'
)
    . '</div>',
  );

  // $form_state['storage'] has no specific drupal meaning, but it is
  // traditional to keep variables for multistep forms there.
  $step = empty($form_state['storage']['step']) ? 1 : $form_state['storage']['step'];
  $form_state['storage']['step'] = $step;

  $stop = 'here';
  
  switch ($step) {
    case 1:
      $form['step1'] = array(
        '#type' => 'fieldset',
        '#title' => t("Step 1: $name ==> Select Host Name of system the OS is associated with"),
      );
      $form['step1']['hostname'] = array(
            '#type' => 'radios',
	    '#options' => $lst, //$computer_list,
        '#title' => t('Select the hostame of the system the info file is related to.'),
        '#default_value' => empty($form_state['values']['step1']['hostname']) ? 'xx' : $form_state['values']['step1']['hostname'],
        '#required' => TRUE,
      );
      break;

//--------------------------------------------------------------------------
    case 2:
      $stop = 'here';
      $hn = $form_state['values']['step1']['hostname'];
      $form_state['hname'] = $hn;
      $form['step2'] = array(
        '#type' => 'fieldset',
        '#title' => t("Step 2: Enter the Primay OS information for ==> $lst[$hn]"),
      );

      $form['step2']['os_type'] = array(
					'#title' => t('Select Primary OS type'),
					'#type' => 'select',
					'#options' => array('W' => t('Windows'),  'L' => t('Linux'), 'S' => t('Solaris'), ),
					'#default_value' => empty($form_state['values']['step2']['os_type']) ? '' : $form_state['values']['step2']['os_type'],
					'#required' => TRUE,
					);

      $form['step2']['os_version'] = array(
					   '#title' => t('your os version string'),
					   '#type' => 'textfield',
					   
					   '#default_value' => empty($form_state['values']['step2']['os_version']) ? '' : $form_state['values']['step2']['os_version'],
					   '#required' => TRUE,
					   );

      $form['step2']['os_secd_num'] = array(
					    '#title' => t('Number of Secondary OS'),
					    '#type' => 'select',
					    '#options' => drupal_map_assoc(range(0, 5)),
					    );

      break;
//--------------------------------------------------------------------------------------------

    case 3:
      $stop = 'here';
      $hn = $form_state['hname'];
      $sosnum = $form_state['values']['step2']['os_secd_num'];


      for ($i = 0; $i < $sosnum; $i++){
      $form['step3'][$i] = array(
        '#type' => 'fieldset',
        '#title' => t("Step 3: Enter secondary OS information for ==> $lst[$hn]"),
      );

      

      $form['step3'][$i]['os_type'] = array(
					'#title' => t('Select Secondary OS type'),
					'#type' => 'select',
					'#options' => array( 'W' => t('Windows'),  'L' => t('Linux'), 'S' => t('Solaris'), ),
					//'#default_value' => empty($form_state['values']['step2']['os_type']) ? '' : $form_state['values']['step2']['os_type'],
					'#required' => TRUE,
                    '#wight' => $i,
					);

      $form['step3'][$i]['os_version'] = array(
					   '#title' => t('your os version string'),
					   '#type' => 'textfield',
					  // '#default_value' => empty($form_state['values']['step2']['os_version']) ? '' : $form_state['values']['step2']['os_version'],
					   '#required' => TRUE,
                        '#wight' => $i +1,
					   );

      } //end for
      
      break;
      //---------------------------------------------------------------------------------------------------

  } // end of switch




  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t("Previous step"),

      // Since all info will be discarded, don't validate on 'prev'.
      '#limit_validation_errors' => array(),
      // #submit is required to use #limit_validation_errors
      '#submit' => array('input_os_data_1_submit'),
      '#ajax' => array(
        'wrapper' => 'wonk-form-wrapper',
        'callback' => 'input_os_data_1_callback',
      ),
    );
  }



  if ($step < 3) {
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next step'),
      '#ajax' => array(
        'wrapper' => 'wonk-form-wrapper',
        'callback' => 'input_os_data_1_callback',
      ),
    );
  }

  if ($step == 3) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Submit your information"),
    );
  }





  return $form;
}

function input_os_data_1_callback($form, $form_state) {
  $stop ='here';
  return $form;
}

/**
 * Submit function for ajax_example_wizard.
 *
 * In AJAX this is only submitted when the final submit button is clicked,
 * but in the non-javascript situation, it is submitted with every
 * button click.
 */
function input_os_data_1_submit($form, &$form_state) {

  $stop = 'here';  
  
  // Save away the current information.
  $current_step = 'step' . $form_state['storage']['step'];
  if (!empty($form_state['values'][$current_step])) {
    $form_state['storage']['values'][$current_step] = $form_state['values'][$current_step];
  }

  // Increment or decrement the step as needed. Recover values if they exist.
  if ($form_state['triggering_element']['#value'] == t('Next step')) {
    $form_state['storage']['step']++;
    // If values have already been entered for this step, recover them from
    // $form_state['storage'] to pre-populate them.
    $step_name = 'step' . $form_state['storage']['step'];
    if (!empty($form_state['storage']['values'][$step_name])) {
      $form_state['values'][$step_name] = $form_state['storage']['values'][$step_name];
    }
  }
  if ($form_state['triggering_element']['#value'] == t('Previous step')) {
    $form_state['storage']['step']--;
    // Recover our values from $form_state['storage'] to pre-populate them.
    $step_name = 'step' . $form_state['storage']['step'];
    $form_state['values'][$step_name] = $form_state['storage']['values'][$step_name];
  }

  // If they're done, submit.
  if ($form_state['triggering_element']['#value'] == t('Submit your information')) {
    $value_message = t('Your information has been submitted:') . ' ';
    foreach ($form_state['storage']['values'] as $step => $values) {
      $value_message .= "$step: ";
      foreach ($values as $key => $value) {
        $value_message .= "$key=$value, ";
      }
    }
    drupal_set_message($value_message);
    $form_state['rebuild'] = FALSE;
    return;
  }

  // Otherwise, we still have work to do.
  $form_state['rebuild'] = TRUE;
}

