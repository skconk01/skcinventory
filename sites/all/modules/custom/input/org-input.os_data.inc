




functon input_os_data_2($from, $$from_state){

  $form['user'] = array(
      '#title' => t('user'),
      '#type' => 'textfield',
      '#maxlength' => 16,
      '#size' => 16,
      '#required' => TRUE,
      '#default_value' => "$name",
			);


  //-----------------------------------------------------------------------------
  return $form;
} //end of input_os_data_2








/* //////////////// Tutorial Example 9 ////////////////////// */

/* /\** */
/*  * Example 9: A form with a dynamically added new fields. */
/*  * */
/*  * This example adds default values so that when the form is rebuilt, */
/*  * the form will by default have the previously-entered values. */
/*  * */
/*  * From handbook page http://drupal.org/node/717746. */
/*  * */
/*  * @see form_example_tutorial_9_add_name() */
/*  * @see form_example_tutorial_9_remove_name() */
/*  * @see form_example_tutorial_9_submit() */
/*  * @see form_example_tutorial_9_validate() */
/*  * @ingroup form_example */
/*  *\/ */
/* function input_example_tutorial_9($form, &$form_state) { */

/*   // We will have many fields with the same name, so we need to be able to */
/*   // access the form hierarchically. */
/*   $form['#tree'] = TRUE; */

/*   $form['description'] = array( */
/*     '#type' => 'item', */
/*     '#title' => t('A form with dynamically added new fields'), */
/*   ); */

/*   if (empty($form_state['num_names'])) { */
/*     $form_state['num_names'] = 1; */
/*   } */

/*   // Build the number of name fieldsets indicated by $form_state['num_names'] */
/*   for ($i = 1; $i <= $form_state['num_names']; $i++) { */
/*     $form['name'][$i] = array( */
/*       '#type' => 'fieldset', */
/*       '#title' => t('Name #@num', array('@num' => $i)), */
/*       '#collapsible' => TRUE, */
/*       '#collapsed' => FALSE, */
/*     ); */

/*     $form['name'][$i]['first'] = array( */
/*       '#type' => 'textfield', */
/*       '#title' => t('First name'), */
/*       '#description' => t("Enter first name."), */
/*       '#size' => 20, */
/*       '#maxlength' => 20, */
/*       '#required' => TRUE, */
/*     ); */
/*     $form['name'][$i]['last'] = array( */
/*       '#type' => 'textfield', */
/*       '#title' => t('Enter Last name'), */
/*       '#required' => TRUE, */
/*     ); */
/*     $form['name'][$i]['year_of_birth'] = array( */
/*       '#type' => 'textfield', */
/*       '#title' => t("Year of birth"), */
/*       '#description' => t('Format is "YYYY"'), */
/*     ); */
/*   } */
/*   $form['submit'] = array( */
/*     '#type' => 'submit', */
/*     '#value' => 'Submit', */
/*   ); */

/*   // Adds "Add another name" button */
/*   $form['add_name'] = array( */
/*     '#type' => 'submit', */
/*     '#value' => t('Add another name'), */
/*     '#submit' => array('form_example_tutorial_9_add_name'), */
/*   ); */

/*   // If we have more than one name, this button allows removal of the */
/*   // last name. */
/*   if ($form_state['num_names'] > 1) { */
/*     $form['remove_name'] = array( */
/*       '#type' => 'submit', */
/*       '#value' => t('Remove latest name'), */
/*       '#submit' => array('form_example_tutorial_9_remove_name'), */
/*       // Since we are removing a name, don't validate until later. */
/*       '#limit_validation_errors' => array(), */
/*     ); */
/*   } */

/*   return $form; */
/* } */

/* /\** */
/*  * Submit handler for "Add another name" button on form_example_tutorial_9(). */
/*  * */
/*  * $form_state['num_names'] tells the form builder function how many name */
/*  * fieldsets to build, so here we increment it. */
/*  * */
/*  * All elements of $form_state are persisted, so there's no need to use a */
/*  * particular key, like the old $form_state['storage']. We can just use */
/*  * $form_state['num_names']. */
/*  *\/ */
/* function input_example_tutorial_9_add_name($form, &$form_state) { */
/*   // Everything in $form_state is persistent, so we'll just use */
/*   // $form_state['add_name'] */
/*   $form_state['num_names']++; */

/*   // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again. */
/*   $form_state['rebuild'] = TRUE; */
/* } */


/* function input_example_tutorial_9_remove_name($form, &$form_state) { */
/*   if ($form_state['num_names'] > 1) { */
/*     $form_state['num_names']--; */
/*   } */

/*   // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again. */
/*   $form_state['rebuild'] = TRUE; */
/* } */

/* /\** */
/*  * Validate function for form_example_tutorial_9(). */
/*  * */
/*  * Adds logic to validate the form to check the validity of the new fields, */
/*  * if they exist. */
/*  *\/ */
/* function input_example_tutorial_9_validate($form, &$form_state) { */

/*   for ($i = 1; $i <= $form_state['num_names']; $i++) { */
/*     $year_of_birth = $form_state['values']['name'][$i]['year_of_birth']; */

/*     if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) { */
/*       form_set_error("name][$i][year_of_birth", t('Enter a year between 1900 and 2000.')); */
/*     } */
/*   } */
/* } */

/* /\** */
/*  * Submit function for form_example_tutorial_9(). */
/*  *\/ */
/* function input_example_tutorial_9_submit($form, &$form_state) { */
/*   $output = t("Form 9 has been submitted."); */
/*   for ($i = 1; $i <= $form_state['num_names']; $i++) { */
/*     $output .= t("@num: @first @last (@date)... ", array('@num' => $i, '@first' => $form_state['values']['name'][$i]['first'], */
/*       '@last' =>  $form_state['values']['name'][$i]['last'], '@date' =>  $form_state['values']['name'][$i]['year_of_birth'])); */
/*   } */
/*   drupal_set_message($output); */
/* } */
