<?php

/**
 * @file
 * Admin functions for the PBS TV Schedule module.
 */

/**
 * General module settings form.
 *
 * Normally this would be handled by system_settings_form() and
 * system_settings_form_submit(), but validation is needed for elements in the
 * feed config tabledrag.
 *
 * @see system_settings_form()
 */
function pbs_tv_schedule_settings(array $form, array &$form_state) {
  $form['#attached']['css'][] = drupal_get_path('module', 'pbs_tv_schedule')
    . '/css/pbs_tv_schedule.admin.css';

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
    '#weight' => 10,
  );

  $form['pbs_tv_schedule_call_sign'] = array(
    '#title' => t('Station Call Sign'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pbs_tv_schedule_call_sign'),
    '#required' => TRUE,
    '#description' => t('Call letters as used by PBS to identify the 
      station, eg "WNET" or "WNJT"'),
    '#weight' => 20,
  );

  $form['pbs_tv_schedule_api_key'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pbs_tv_schedule_api_key'),
    '#required' => TRUE,
    '#description' => t('TV Schedules API key (provided by PBS).'),
    '#weight' => 30,
  );

  $form['api_connection_test'] = array(
    '#type' => 'button',
    '#value' => t('Test API Connection'),
    '#ajax' => array(
      'callback' => '_pbs_tv_schedule_api_test',
      'wrapper' => 'api-test-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#weight' => 40,
  );

  if (variable_get('pbs_tv_schedule_api_key')
    && variable_get('pbs_tv_schedule_call_sign')) {
    $client = pbs_tv_schedule_get_api_client(NULL, NULL, FALSE);

    try {
      $feeds = $client->getFeeds();

      $form['pbs_tv_schedule_feeds_config']['#tree'] = TRUE;
      $form['pbs_tv_schedule_feeds_config_tabledrag'] = array(
        '#type' => 'markup',
        '#markup' => t('<label for="@for">@label</label>', array(
          '@for' => 'edit-pbs-tv-schedule-feeds-config-tabledrag',
          '@label' => t('Feeds Configuration'),
        )),
        '#weight' => 60,
        '#prefix' => '<div class="form-item">',
        '#suffix' => t('<div class="description">!description</div></div>', array(
          '!description' => t('Re-order feeds as desired. Use the 
            <strong>Enabled</strong> and <strong>Default</strong> fields for 
            each feed to set properties for if/how the feeds should display on
            schedule pages.'),
        )),
      );
      $config = variable_get('pbs_tv_schedule_feeds_config');
      if (!$config) {
        $config = array_fill_keys(array_keys($feeds), array(
          'weight' => 0,
          'enabled' => TRUE,
          'default' => FALSE,
        ));
      }
      uasort($config, 'drupal_sort_weight');

      // This hidden element will capture the default selection in the tabledrag
      // elements.
      $feed_default = variable_get('pbs_tv_schedule_feed_default');
      $form['pbs_tv_schedule_feed_default'] = array(
        '#type' => 'hidden',
        '#default_value' => $feed_default,
      );

      foreach ($config as $feed => $item) {
        $enabled_field_name = 'pbs_tv_schedule_feeds_config[' . $feed . '][enabled]';
        $form['pbs_tv_schedule_feeds_config'][$feed] = array(
          'name' => array(
            '#markup' => check_plain($feeds[$feed]['full_name']),
          ),
          'enabled' => array(
            '#type' => 'checkbox',
            '#default_value' => $item['enabled'],
          ),
          'default' => array(
            '#type' => 'radio',
            '#name' => 'pbs_tv_schedule_feed_default',
            '#return_value' => $feed,
            '#default_value' => ($feed_default === $feed ? TRUE : FALSE),
            '#states' => array(
              'disabled' => array(
                ':input[name="' . $enabled_field_name . '"]' => array(
                  'checked' => FALSE,
                ),
              ),
            ),
          ),
          'weight' => array(
            '#type' => 'weight',
            '#title' => t('Weight'),
            '#default_value' => $item['weight'],
            '#delta' => 10,
            '#title_display' => 'invisible',
            '#attributes' => array(
              'class' => array('pbs-tv-schedule-feed-weight'),
            ),
          ),
        );
      }
    }
    catch (PbsTvScheduleClientException $e) {
      watchdog_exception('pbs_tv_schedule', $e);
    }
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validation handler for the pbs_tv_schedule_settings() form.
 *
 * @see pbs_tv_schedule_settings()
 * @see pbs_tv_schedule_settings_submit()
 */
function pbs_tv_schedule_settings_validate(array $form, array &$form_state) {
  if (isset($form_state['values']['pbs_tv_schedule_feed_default'])) {
    $feed_default = $form_state['values']['pbs_tv_schedule_feed_default'];
    $config = $form_state['values']['pbs_tv_schedule_feeds_config'];
    if (!$config[$feed_default]['enabled']) {
      form_set_error(
        'pbs_tv_schedule_feeds_config][' . $feed_default . '][enabled',
        t('Default feed in <strong>Feeds Configuration</strong> must be 
          enabled.')
      );
    }
  }
}

/**
 * Submission handler for the pbs_tv_schedule_settings() form.
 *
 * @see pbs_tv_schedule_settings()
 * @see pbs_tv_schedule_settings_validate()
 * @see system_settings_form_submit()
 */
function pbs_tv_schedule_settings_submit(array $form, array &$form_state) {
  system_settings_form_submit($form, $form_state);
}

/**
 * Create table drag element for feed ordering.
 *
 * @param array $variables
 *   Theme variables.
 *
 * @return string
 *   Form output.
 *
 * @throws Exception
 */
function theme_pbs_tv_schedule_settings(array $variables) {
  $form = $variables['form'];

  if (isset($form['pbs_tv_schedule_feeds_config'])) {
    $rows = array();

    foreach (element_children($form['pbs_tv_schedule_feeds_config']) as $id) {
      $rows[] = array(
        'data' => array(
          drupal_render($form['pbs_tv_schedule_feeds_config'][$id]['name']),
          drupal_render($form['pbs_tv_schedule_feeds_config'][$id]['enabled']),
          drupal_render($form['pbs_tv_schedule_feeds_config'][$id]['default']),
          drupal_render($form['pbs_tv_schedule_feeds_config'][$id]['weight']),
        ),
        'class' => array('draggable'),
      );
    }

    $markup = theme('table', array(
      'header' => array(t('Name'), t('Enabled'), t('Default'), t('Weight')),
      'rows' => $rows,
      'attributes' => array('id' => 'pbs-tv-schedule-feeds-config-tabledrag'),
    ));
    $form['pbs_tv_schedule_feeds_config_tabledrag']['#markup'] .= $markup;

    drupal_add_tabledrag(
      'pbs-tv-schedule-feeds-config-tabledrag',
      'order',
      'sibling',
      'pbs-tv-schedule-feed-weight'
    );
  }

  return drupal_render_children($form);
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
