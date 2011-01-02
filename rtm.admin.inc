<?php
/**
 * @file rtm.admin.inc
 */
/**
 * Form builder. Configure RTM settings.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function rtm_admin_settings() {
  $api_key = variable_get('rtm_api_key', NULL);
  $form['rtm_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('RTM API Key'),
    '#description' => t('Get your API key !here', 
      array('!here' => l('here', url('http://www.rememberthemilk.com/services/api/keys.rtm', 
        array('absolute' => TRUE)
      ))
    )),
    '#default_value' => $api_key
  ); 
  // Show all RTM methods available using the stored API key.
  if ($api_key) {
    $methods = rtm_get_methods($api_key);
    $rtm_functions = rtm_function_list();
    $form['methods'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available Methods'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    foreach($methods as $method) {
      if ($rtm_functions[$method]) {
        $value = t('Use function: !function', 
                   array('!function' => '<strong>'. $rtm_functions[$method] .'</strong>'));
      } else {
        $value = 'Use rtm_call_method($args)';
      }
      $form['methods'][$method] = array(
        '#type' => 'item',
        '#title' => $method,
        '#description' => t('This Remember the Milk method is available using '
                           .'the stored API key.'),
        '#value' => $value,
      );
    }
  } 

  return system_settings_form($form);
}


