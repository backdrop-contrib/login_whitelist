<?php
/**
 * @file
 * Admin forms to manage module
 *
 */

/**
 * 
 * Settings form for module.
 *
 */
function login_whitelist_settings_form() {
  $config    = config('login_whitelist.settings');
  $whitelist = $config->get('whitelist');

  $form = array();

  $form['all_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow login to all registered active users'),
    '#default_value' => $config->get('all_users'),
    '#description' => '<strong>' . t('If this option is selected, login to site should be allowed to all registered active users, ignoring data from field below.') . '</strong>', 
  );
  $form['whitelist'] = array(
    '#type' =>  'textarea',
    '#title' => t('Whitelist'),
    '#default_value' => $whitelist,
    '#description' => t('If you need short list of usernames or emails allowed for login to this site, place it here, one per line, see an example below:') 
    . '<em>'     
    . '<br />johndow'
    . '<br />jane.dow@example.com'
    . '<br />another-username'
    . '</em>'
    . '<br /><strong>'    
    . t('Please note: Make sure checkbox above is not selected and filled usernames or users emails is registered on this site.')
    . '</strong>',
  );
  $form['status_code'] = array(
    '#type' => 'select',
    '#title' => t('HTTP status code'),
    '#options' => array(
      '403' => t('403 Forbidden'),
      '404' => t('404 Not found'),
    ),
    '#default_value' => $config->get('status_code'),
    '#description' => t('Select HTTP status code which should be returned to unwanted visitor.'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

function login_whitelist_settings_form_validate($form, &$form_state) {

  $form_values = $form_state['values'];
  
  if ($form_values['all_users'] == 0 && empty(trim($form_values['whitelist']))) {
    form_set_error('', t('Please fill some Usernames or Emails to "Whitelist" field or allow login to all users!'));
  }
}  

function login_whitelist_settings_form_submit($form, &$form_state) {
  $config = config('login_whitelist.settings');

  $config->set('status_code', $form_state['values']['status_code']);
  $config->set('whitelist',   trim($form_state['values']['whitelist']));
  $config->set('all_users',   $form_state['values']['all_users']);
  $config->save();
  
  backdrop_set_message(t('The configuration options have been saved.'));
}