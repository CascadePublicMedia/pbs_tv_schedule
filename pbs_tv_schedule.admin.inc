<?php

/**
 * @file
 * Admin functions for the PBS TV Schedule module.
 */

/**
 * General module settings.
 *
 * @return array
 *   Render array from system_settings_form().
 */
function pbs_tv_schedule_settings() {
  $form = array();

  // API test results will be displayed here.
  $form['test_results'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#value' => '',
    '#attributes' => array(
      'id' => 'api-test-wrapper',
      'class' => array('element-hidden'),
    ),
    '#prefix' => '<div id="api-test-wrapper">',
    '#suffix' => '</div>',
  );

  $form['pbs_tv_schedule_call_sign'] = array(
    '#title' => t('Station Call Sign'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pbs_tv_schedule_call_sign'),
    '#required' => TRUE,
    '#description' => t('Call letters as used by PBS to identify the 
      station, eg "WNET" or "WNJT"'),
  );

  $form['pbs_tv_schedule_api_key'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pbs_tv_schedule_api_key'),
    '#required' => TRUE,
    '#description' => t('TV Schedules API key (provided by PBS).'),
  );

  if (variable_get('pbs_tv_schedule_api_key')
    && variable_get('pbs_tv_schedule_call_sign')) {
    $client = pbs_tv_schedule_get_api_client(NULL, NULL, FALSE);

    try {
      $feeds = $client->getFeeds();

      $options = array();
      foreach ($feeds as $feed) {
        $options[$feed['short_name']] = $feed['full_name'];
      }

      $form['pbs_tv_schedule_feed_default'] = array(
        '#title' => t('Default Feed'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => variable_get('pbs_tv_schedule_feed_default'),
        '#description' => t('The default feed to use for schedule pages.'),
      );
    }
    catch (PbsTvScheduleClientException $e) {
      watchdog_exception('pbs_tv_schedule', $e);
    }
  }

  $form['api_connection_test'] = array(
    '#type' => 'button',
    '#value' => t('Test API Connction'),
    '#ajax' => array(
      'callback' => '_pbs_tv_schedule_api_test',
      'wrapper' => 'api-test-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return system_settings_form($form);
}

/**
 * AJAX callback: Test form submit handler for API test.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Submitted form state.
 *
 * @return array
 *   Returns a response array.
 */
function _pbs_tv_schedule_api_test(array $form, array &$form_state) {
  $client = pbs_tv_schedule_get_api_client(
    $form_state['values']['pbs_tv_schedule_api_key'],
    $form_state['values']['pbs_tv_schedule_call_sign'],
    FALSE
  );

  $element = $form['test_results'];
  $element['#attributes']['class'] = array('messages');

  // Set default failure status.
  $status = t('API connection attempt failed. Check API key and try 
    again. Additional details may be found in site logs.');
  $element['#attributes']['class'][] = 'error';

  try {
    $response = $client->getToday();
    if (!empty($response)) {
      $status = t('API connection test succeeded!');
      $element['#attributes']['class'][] = 'status';
    }
  }
  catch (PbsTvScheduleClientException $e) {
    watchdog_exception('pbs_tv_schedule', $e);
  }

  $element['#value'] = $status;

  return $element;
}
