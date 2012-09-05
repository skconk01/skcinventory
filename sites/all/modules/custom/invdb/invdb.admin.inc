<?php
// $Id$

/**
 * @file
 * Admin page callback for the trails module.
 */

/**
 * Builds and returns the invdb settings form.
 */
function invdb_admin_settings() {
  $form['invdb_block_max'] = array(
    '#type' => 'select',
    '#title' => t('Maximum number of items to display'),
    '#options' => drupal_map_assoc(range(1, 200)),
    '#default_value' => variable_get('invdb_block_max', ''),
    '#description' => t('This will set the maximum allowable number that can be displayed in a history block'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}