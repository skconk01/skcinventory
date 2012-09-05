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
    
  

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('This form will collect the OS  information about your system. <br \>'),
  );



// get a list of computers used by this user
  $computer_list = invdb_get_computer_list($name);


  $lst = array();
  //$lst['0'] = '';
  foreach ($computer_list as $computer){
  
    $inv_id = $computer->inv_id;
    $lst[$inv_id] = $computer->hostname;
  }
  
 
// Added AJAX callback.
  $form['computer_name']['name'] = array(
    '#title' => t('Select the hostame of the system the info file is related to.'),
    '#type' => 'radios',
    '#options' => $lst,
    '#ajax' => array(
      //'callback' => 'input_os_data_ajax_callback',
        'callback' => 'ajax_example_add_more',
	'wrapper' => 'skc_wrapper',
      //'wrapper' => 'names-fieldset-wrapper',
     ),
  );
  
  // Setting an empty element with a wrapper to be populated.
  $form['computer_name']['os_data'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="skc_wrapper">',
    '#suffix' => '</div>',
  );
  

  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  //-----------------------------------------------------------------------------
  return $form;
}


/**
 * AJAX callback for OS verification.
 */
function input_os_data_ajax_callback($form, $form_state) {

  return $form['computer_name']['os_data'];
}


  //===================================================================================================
/**
 * function from ajax exampel
 *
 */
function ajax_example_add_more($form, &$form_state, $no_js_use = FALSE) {
  $form['description'] = array(
    '#markup' => '<div>' . t('This example shows an add-more and a remove-last button. The <a href="!ajax">AJAX version</a> does it without page reloads; the <a href="!multistep">non-js version</a> is the same code but simulates a non-javascript environment, showing it with page reloads.',
      array('!ajax' => url('examples/ajax_example/add_more'), '!multistep' => url('examples/ajax_example/add_more_no_js')))
    . '</div>',
  );

  // Because we have many fields with the same values, we have to set
  // #tree to be able to access them.
  $form['#tree'] = TRUE;
  $form['names_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('People coming to the picnic'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="names-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  $stop = 'here';
  
  // Build the fieldset with the proper number of names. We'll use
  // $form_state['num_names'] to determine the number of textfields to build.
  if (empty($form_state['num_names'])) {
    $form_state['num_names'] = 1;
  }
  for ($i = 0; $i < $form_state['num_names']; $i++) {
    $form['names_fieldset']['name'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
    );
  }
  $form['names_fieldset']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('ajax_example_add_more_add_one'),
    // See the examples in ajax_example.module for more details on the
    // properties of #ajax.
    '#ajax' => array(
      'callback' => 'ajax_example_add_more_callback',
      'wrapper' => 'names-fieldset-wrapper',
    ),
  );
  if ($form_state['num_names'] > 1) {
    $form['names_fieldset']['remove_name'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('ajax_example_add_more_remove_one'),
      '#ajax' => array(
        'callback' => 'ajax_example_add_more_callback',
        'wrapper' => 'names-fieldset-wrapper',
      ),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  // This simply allows us to demonstrate no-javascript use without
  // actually turning off javascript in the browser. Removing the #ajax
  // element turns off AJAX behaviors on that element and as a result
  // ajax.js doesn't get loaded.
  // For demonstration only! You don't need this.
  if ($no_js_use) {
    // Remove the #ajax from the above, so ajax.js won't be loaded.
    if (!empty($form['names_fieldset']['remove_name']['#ajax'])) {
      unset($form['names_fieldset']['remove_name']['#ajax']);
    }
    unset($form['names_fieldset']['add_name']['#ajax']);
  }

  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function ajax_example_add_more_callback($form, $form_state) {
  return $form['names_fieldset'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function ajax_example_add_more_add_one($form, &$form_state) {
  $form_state['num_names']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function ajax_example_add_more_remove_one($form, &$form_state) {
  if ($form_state['num_names'] > 1) {
    $form_state['num_names']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */
function ajax_example_add_more_submit($form, &$form_state) {
  $output = t('These people are coming to the picnic: @names',
    array('@names' => implode(', ', $form_state['values']['names_fieldset']['name'])) );
  drupal_set_message($output);
}
/**
 * @} End of "defgroup ajax_degradation_example".
 */
