<?php

/**
 * @file
 * Hooks provided by the PBS TV Schedule module.
 */

/**
 * Alter an API response before it is cached and modified by other methods.
 *
 * This alter hook will not be called for already cached responses, but any
 * changes made in functions implementing this hook will be cached.
 *
 * @param array $response
 *   The API response.
 * @param string $endpoint
 *   The query endpoint.
 *
 * @see PbsTvScheduleClient::get()
 */
function hook_pbs_tv_schedule_api_response_raw_alter(array &$response, $endpoint) {

}

/**
 * Alter the API response for the getFeeds method.
 *
 * @param array $feeds
 *   Feeds data from the API.
 *
 * @see PbsTvScheduleClient::getFeeds()
 */
function hook_pbs_tv_schedule_feeds_alter(array &$feeds) {

}

/**
 * Alter the API response for the getChannels method.
 *
 * @param array $channels
 *   Channels data from the API.
 *
 * @see PbsTvScheduleClient::getChannels()
 */
function hook_pbs_tv_schedule_channels_alter(array &$channels) {

}

/**
 * Alter the API response for the getToday method.
 *
 * @param array $listings
 *   Listings data for today from the API.
 *
 * @see PbsTvScheduleClient::getToday()
 */
function hook_pbs_tv_schedule_today_alter(array &$listings) {

}

/**
 * Alter the API response for the getFullDay method.
 *
 * @param array $listings
 *   Listings data for the date from the API.
 * @param string $date
 *   Date of listings in the format YYYYMMDD.
 *
 * @see PbsTvScheduleClient::getFullDay()
 */
function hook_pbs_tv_schedule_full_day_alter(array &$listings, $date) {

}

/**
 * Alter the API response for the getShowInfo method.
 *
 * @param array $show
 *   Show info from the API.
 *
 * @see PbsTvScheduleClient::getShowInfo()
 */
function hook_pbs_tv_schedule_show_info_alter(array &$show) {

}

/**
 * Alter the API response for the getProgramInfo method.
 *
 * @param array $program
 *   Program info from the API.
 *
 * @see PbsTvScheduleClient::getProgramInfo()
 */
function hook_pbs_tv_schedule_program_info_alter(array &$program) {

}

/**
 * Alter the API response for the getPrograms method.
 *
 * @param array $programs
 *   All programs and associated data from the API.
 *
 * @see PbsTvScheduleClient::getPrograms()
 */
function hook_pbs_tv_schedule_programs_alter(array &$programs) {

}

/**
 * Alter information for a single listing item.
 *
 * @param array $listing
 *   Single listing item details.
 *
 * @see _pbs_tv_schedule_format_listing()
 */
function hook_pbs_tv_schedule_listing_alter(array &$listing) {

}
