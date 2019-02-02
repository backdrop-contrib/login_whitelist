<?php
/**
 * @file
 * Admin forms to configure module
 *
 */

/**
 * 
 * Main settings form for module.
 *
 */
function login_whitelist_main_settings_form() {
  $config = config('login_whitelist.settings');
 
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
    '#default_value' => $config->get('whitelist'),
    '#description' => t('If you need whitelist of usernames or Emails allowed for login to this site, place it here, one per line, see an example below:') 
    . '<em>'     
    . '<br />johndow'
    . '<br />jane.dow@example.com'
    . '<br />another-username'
    . '</em>'
    . '<br /><strong>'    
    . t('Please note: Make sure checkbox above is not selected and filled usernames or users Emails is registered and active on this site.')
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
  $form['log_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Write log for all unwanted login attempts'),
    '#default_value' => $config->get('log_enabled'),
    '#description' => t('If this option is selected, all unwanted login attempts should be written to dblog ("Reports -> Recent log messages") as warning messages of type "login_whitelist".'), 
  );
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

function login_whitelist_main_settings_form_validate($form, &$form_state) {
  
  global $user;
  $form_values = $form_state['values'];

  if ($form_values['all_users'] == 0) { 
    if(empty(trim($form_values['whitelist']))) {
      form_set_error('', t('Please fill some usernames or Emails to "Whitelist" field or allow login to all users!'));
    }
    else {
      $whitelist = login_whitelist_textarea_to_array(trim($form_values['whitelist']));
      $self = in_array($user->name, $whitelist) || in_array($user->mail, $whitelist);     

      if (!$self) {
        form_set_error('', t('Please add to "Whitelist" field your own username or Email to prevent blocking yourself!'));        
      }
    }
  }
}  

function login_whitelist_main_settings_form_submit($form, &$form_state) {
  $config = config('login_whitelist.settings');

  $config->set('status_code', $form_state['values']['status_code']);
  $config->set('whitelist',   trim($form_state['values']['whitelist']));
  $config->set('all_users',   $form_state['values']['all_users']);
  $config->set('log_enabled', $form_state['values']['log_enabled']);
  $config->save();
  
  backdrop_set_message(t('The configuration options have been saved.'));
}

function login_whitelist_ua_string_form() {
  $config = config('login_whitelist.settings');
 
  $form = array();

  $form['add_ua'] = array(
    '#prefix' => '<p>' . t('List of User-Agent strings not allowed for login action to your site (like "bad robots")') . '</p>',
    '#type' => 'fieldset',
    '#title' => t('Add User-Agent string to list blocked'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    
  );
  $form['add_ua']['ua'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#maxlength' => 256,
    '#default_value' => '',
    '#description' => t('User-Agent string known as used by bad robots, examples below:')
      . '<em>'
      . '<br />Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko'
      . '</em>'
      . '<br /><strong>'. t('or') .'</strong>' 
      . '<br />'
      . '<em>drupalgeddon2</em>'
      . '<br />' . t('Please note: the * character is a wildcard for end of string, so record like:')
      . '<br /><em>python-requests/*</em>'
      . '<br />' . t('will block any User-Agent strings starting with "python-requests/" ("python-requests/2.9.0" for example).')
      . '<br /><strong>'
      . t('Any requests to user login or register by using User-Agent string listed below will be rejected.')
      . '</strong>',
  );
  $form['add_ua']['actions'] = array('#type' => 'actions');
  $form['add_ua']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add User-Agent string'),
  );

  $ua_list = $config->get('ua_list');
  $rows = array();
  $header = array(t('User-Agent string'), t('Action'));
  
  if (!empty($ua_list)) {
    foreach ($ua_list as $key => $ua_string) {
      $rows[] = array(
        $ua_string,
        l(t('Unblock'), 'admin/config/people/login_whitelist/ua_string/unblock/' . $key),
      );
    }
  }

  $form['ua_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blocked User-Agent strings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    
  );

  $form['ua_list']['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No blocked User-Agent strings available.'),
  );

  return $form;
} 

function login_whitelist_ua_string_form_validate($form, &$form_state) {
  $current_ua = $_SERVER['HTTP_USER_AGENT'];
  $ua_string = trim($form_state['values']['ua']);
  
  if (empty($ua_string)) {
    form_set_error('ua', t('This field cannot be empty!'));
  }
  if ($ua_string === $current_ua) {
    form_set_error('', t('You try to add your own current User-Agent string!'));    
  }
}

function login_whitelist_ua_string_form_submit($form, &$form_state) {
  $config = config('login_whitelist.settings');

  $ua_list = $config->get('ua_list');
  $ua_string = trim($form_state['values']['ua']);
 
  if (in_array($ua_string, $ua_list)) {
    form_set_error('', t('This User-Agent string in the list already!'));
  }
  else {
    $ua_list[md5($ua_string)] = $ua_string;

    asort($ua_list, SORT_NATURAL | SORT_FLAG_CASE);
    $config->set('ua_list', $ua_list);
    $config->save();

    backdrop_set_message(t('Added new User-Agent string: ') . $ua_string);
    
  }
}

/**
 * User-Agent string unblock confirm page.
 *
 */
function login_whitelist_unblock($form, &$form_state, $key) {
  $form['blocked_ua_key'] = array(
    '#type' => 'value',
    '#value' => $key,
  );
  $config = config('login_whitelist.settings');
  $ua_list = $config->get('ua_list');
  if (array_key_exists($key, $ua_list)) {
    $ua_string = $ua_list[$key];
    return confirm_form($form, t('Are you sure you want to unblock %ua_string?', array('%ua_string' => $ua_string)), 'admin/config/people/login_whitelist/ua_string', t('This action cannot be undone.'), t('Unblock'), t('Cancel'));
  }
}

/**
 * Process login_whitelist_unblock form submissions.
 */
function login_whitelist_unblock_submit($form, &$form_state) {
  $blocked_ua_key = $form_state['values']['blocked_ua_key'];
  
  $config = config('login_whitelist.settings');
  $ua_list = $config->get('ua_list');
  
  if (array_key_exists($blocked_ua_key, $ua_list)) {
    $ua_string = $ua_list[$blocked_ua_key];

    unset($ua_list[$blocked_ua_key]);

    asort($ua_list, SORT_NATURAL | SORT_FLAG_CASE);
    $config->set('ua_list', $ua_list);
    $config->save();

    watchdog('login_whitelist', 'Unblocked User-Agent string %ua', array('%ua' => $ua_string));
    backdrop_set_message(t('The User-Agent string %ua was unblocked.', array('%ua' => $ua_string)));
    $form_state['redirect'] = 'admin/config/people/login_whitelist/ua_string';
  }
}