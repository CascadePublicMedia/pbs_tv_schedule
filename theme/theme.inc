<?php

/**
 * @file
 * Theme functions for the PBS TV Schedule module.
 */

/**
 * Preprocessor for pbs_tv_schedule_schedule form.
 *
 * @see pbs_tv_schedule_theme()
 * @see pbs_tv_schedule_schedule()
 */
function template_preprocess_pbs_tv_schedule_schedule(&$variables) {
}

/**
 * Preprocessor for pbs_tv_schedule_schedule_week_filter form.
 *
 * @see pbs_tv_schedule_theme()
 * @see pbs_tv_schedule_schedule_week_filter()
 */
function template_preprocess_pbs_tv_schedule_schedule_week_filter(&$variables) {
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-date.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_date(&$variables) {
  $variables['items_past'] = array();
  $variables['items_future'] = array();

  // If the date being viewed is today, break the items in to groups by time.
  $now = new DateTime();
  if ($variables['date']->format('Ymd') == $now->format('Ymd')) {
    foreach ($variables['items'] as $item) {
      try {
        $end_time = $item['#start_time']->add(
          new DateInterval('PT' . $item['#duration'] . 'M')
        );
      }
      catch (Exception $e) {
        watchdog_exception('pbs_tv_schedule', $e);
        continue;
      }

      if ($end_time < $now) {
        $variables['items_past'][] = $item;
      }
      else {
        $variables['items_future'][] = $item;
      }
    }
  }
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-search.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_search(&$variables) {
  // Reorganize listing items by date for search view.
  $items_by_date = array();
  foreach ($variables['items'] as $item) {
    $key = $item['#start_time']->format('D, M. d');
    if (!isset($items_by_date[$key])) {
      $items_by_date[$key] = array();
    }
    $items_by_date[$key][] = $item;
  }
  $variables['items'] = $items_by_date;
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-date-item.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_date_item(&$variables) {
  drupal_add_library('system', 'drupal.ajax');

  if ($variables['duration']) {
    $variables['duration_formatted'] = format_interval(
      $variables['duration'] * 60
    );
  }

  if (empty($variables['description'])) {
    $variables['description'] = t('<em>No description.</em>');
  }

  _pbs_tv_schedule_add_icons($variables);
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-week.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_week(&$variables) {
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-week-item.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_week_item(&$variables) {
  if ($variables['duration']) {
    $variables['duration_formatted'] = format_interval(
      $variables['duration'] * 60
    );
  }

  _pbs_tv_schedule_add_icons($variables);
}

/**
 * Add icons data to a $variables render array.
 *
 * @param array $variables
 *   A typical render array with the following expected boolean values:
 *    - closed_captions
 *    - hd
 *    - stereo.
 */
function _pbs_tv_schedule_add_icons(array &$variables) {
  $base_path = drupal_get_path('module', 'pbs_tv_schedule');

  if (isset($variables['closed_captions']) && $variables['closed_captions']) {
    $variables['closed_captions_icon'] = array(
      '#theme' => 'image',
      '#path' => $base_path . '/images/cc.png',
      '#alt' => t('Closed captions available.'),
      '#title' => t('Closed captions available.'),
    );
  }

  if (isset($variables['hd']) && $variables['hd']) {
    $variables['hd_icon'] = array(
      '#theme' => 'image',
      '#path' => $base_path . '/images/hd.png',
      '#alt' => t('Available in high definition.'),
      '#title' => t('Available in high definition.'),
    );
  }

  if (isset($variables['stereo']) && $variables['stereo']) {
    $variables['stereo_icon'] = array(
      '#theme' => 'image',
      '#path' => $base_path . '/images/stereo.png',
      '#alt' => t('Available in stereo.'),
      '#title' => t('Available in stereo.'),
    );
  }
}

/**
 * Implements template_preprocess().
 *
 * @see theme/pbs-tv-schedule-schedule-no-results.tpl.php
 */
function template_preprocess_pbs_tv_schedule_schedule_no_results(&$variables) {
}
