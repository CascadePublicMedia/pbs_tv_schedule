<?php

/**
 * @file
 * Views hooks implemented for the PBS TV Schedule module.
 */

/**
 * Implements hook_views_data().
 */
function pbs_tv_schedule_views_data() {
  $data['pbs_tv_schedule_program']['table']['group'] = t('PBS TV Schedule');
  $data['pbs_tv_schedule_program']['table']['base'] = array(
    'field' => 'cid',
    'title' => t('PBS TV Schedule: Programs'),
    'help' => t('Cached data for all programs from the PBS TV Schedule API.'),
  );

  // Primary key.
  $data['pbs_tv_schedule_program']['cid'] = array(
    'title' => t('Primary key'),
    'help' => t('The primary key for this record.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'sort' => array('handler' => 'views_handler_sort'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // Program ID.
  $data['pbs_tv_schedule_program']['program_id'] = array(
    'title' => t('Program ID'),
    'help' => t('Program ID (unique).'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'sort' => array('handler' => 'views_handler_sort'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // Title.
  $data['pbs_tv_schedule_program']['title'] = array(
    'title' => t('Title'),
    'help' => t('Program title.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'sort' => array('handler' => 'views_handler_sort'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // Description.
  $data['pbs_tv_schedule_program']['description'] = array(
    'title' => t('Description'),
    'help' => t('Program description.'),
    'field' => array('handler' => 'views_handler_field'),
    'filter' => array('handler' => 'views_handler_filter_string'),
  );

  // External ID.
  $data['pbs_tv_schedule_program']['external_id'] = array(
    'title' => t('External ID'),
    'help' => t('External ID.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'sort' => array('handler' => 'views_handler_sort'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  return $data;
}
