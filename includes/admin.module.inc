<?php
/**
 * @file admin.module.inc
 * Houses our admin functions.
 */

/**
 * Main settings form
 */
function _flipkey_main_settings() {
  //Main Form settings.
  $form['main'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Flipkey API Settings'),
    '#description' => t('Settings related to your flipkey account.'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
    '#weight'	   => -50,
    '#group'       => 'main',
  );
  
  $form['main']['flipkey_api_key'] = array(
    '#title'            => t('API Key'),
    '#description'      => t('This is the API key for your flipkey account.'),
    '#type'             => 'textfield',
    '#required'         => TRUE,
    '#default_value'    => variable_get('flipkey_api_key', NULL),
    '#element_validate' => array('_flipkey_api_key_validate'),
    '#max_length'       => 75,
    '#weight'           => -50,
    '#group'            => 'main',
  );  
  
  $form['main']['flipkey_frontdesk_id'] = array(
    '#title'            => t('Front desk ID'),
    '#description'      => t('This is the front desk ID for your flipkey account.'),
    '#type'             => 'textfield',
    '#required'         => TRUE,
    '#default_value'    => variable_get('flipkey_frontdesk_id', NULL),
    '#element_validate' => array('_flipkey_frontdesk_id_vaidate'),
    '#max_length'       => 12,
    '#weight'           => -50,
    '#group'            => 'main',
  );
  
  $form['main']['flipkey_property_id_key'] = array(
    '#title'         => t('Property ID key'),
    '#description'   => t('Select the $node->%key that you wish to assign as the property id. You need this to get the review for a specific property.'),
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#default_value' => variable_get('flipkey_property_id_key', NULL),
    '#max_length'    => 36,
    '#weight'        => -49,
    '#group'         => 'main',
  );
  $node_types = array_map('check_plain', node_get_types('names'));
  $form['main']['flipkey_node_types'] = array(
    '#title'         => t('Flipkey node types.'),
    '#description'   => t('Select which node types flipkey should monitor for reviews.'),
    '#type'          => 'select',
    '#multiple'      => TRUE,
    '#required'      => TRUE,
    '#options'       => $node_types,
    '#default_value' => variable_get('flipkey_node_types',array()),
    '#weight'        => -48,
    '#group'         => 'main',
  );
  
      //Main Form settings.
  
  $form['tools'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Flipkey Tools'),
    '#description' => t('Utilities to manage your FlipKey Reviews'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
    '#weight'	   => -40,
    '#group'       => 'tools',
  );

  $attributes['class'] = 'update-flipkey';
  $attributes['query'] = drupal_get_destination();
  
  $items[] = l('Update All Reviews', 'flipkey/update/all', $attributes);
  
  $lastupdated = 	variable_get('flipkey_last_updated_node', 0);
  
  $items[] = 'Last updated node: '.$lastupdated;
  
  $form['tools']['updatelink'] = array(
    '#title'       => t('Manual Update'),
    '#description' => t('Perform a manual update'),
    '#prefix' => '<p>',
    '#value'   => theme('item_list', $items),
    '#suffix'  => '</p>',
    '#group'   => 'tools',
  );

  
  
  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return system_settings_form($form);
}

//Validate that the frontdesk_id is a numeric value only. Validate this.
function _flipkey_frontdesk_id_vaidate($element, &$form_state, $complete_form) {
  //If we are not numeric, then flag an error
  if (!is_numeric($element['#value'])) {
    form_error($element, t('You must enter a numeric value for the front desk key.'));
  }
}

//Validate that the api_key is a numeric value only. Validate this.
function _flipkey_api_key_validate($element, &$form_state, $complete_form) {
  //If we are not numeric, then flag an error
  if (!$element['#value']) {
    form_error($element, t('You must enter your Flipkey Account API Key.'));
  }
}