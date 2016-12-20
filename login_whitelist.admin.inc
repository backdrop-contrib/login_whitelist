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
  $config      = config('login_whitelist.settings');
  $whitelist   = $config->get('whitelist');
  $bad_ua_list = $config->get('bad_ua_list');
  
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
  $form['bad_ua_list'] = array(
    '#type' =>  'textarea',
    '#title' => t('Bad robots User-Agent strings list'),
    '#default_value' => $bad_ua_list,
    '#description' => t('If you know User-Agent strings used by bad robots, place it here, one per line, see an example below:') 
    . '<em>'     
    . '<br />Mozilla/5.0 (Windows NT 5.1; rv:29.0) Gecko/20100101 Firefox/29.0'
    . '<br />Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko'
    . '</em>'
    . '<br /><strong>'    
    . t('Please note: Any GET request to user login using User-Agent string listed above will be rejected.')
    . '</strong>',
  );
  $form['log_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Write log for all unwanted login attempts'),
    '#default_value' => $config->get('log_enabled'),
    '#description' => t('If this option is selected, all unwanted login attempts should be written to dblog ("Reports -> Recent log messages") as warning message of type "login_whitelist".'), 
  );
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

function login_whitelist_settings_form_validate($form, &$form_state) {
  
  global $user;
  $form_values = $form_state['values'];

  if ($form_values['all_users'] == 0) { 
    if(empty(trim($form_values['whitelist']))) {
      form_set_error('', t('Please fill some usernames or emails to "Whitelist" field or allow login to all users!'));
    }
    else {
      $whitelist = login_whitelist_textarea_to_array(trim($form_values['whitelist']));
      $self = in_array($user->name, $whitelist) || in_array($user->mail, $whitelist);     

      if (!$self) {
        form_set_error('', t('Please add to "Whitelist" field your own username or email to prevent blocking yourself!'));        
      }
    }
  }
}  

function login_whitelist_settings_form_submit($form, &$form_state) {
  $config = config('login_whitelist.settings');

  $config->set('status_code', $form_state['values']['status_code']);
  $config->set('whitelist',   trim($form_state['values']['whitelist']));
  $config->set('bad_ua_list', trim($form_state['values']['bad_ua_list']));
  $config->set('all_users',   $form_state['values']['all_users']);
  $config->set('log_enabled', $form_state['values']['log_enabled']);
  $config->save();
  
  backdrop_set_message(t('The configuration options have been saved.'));
}