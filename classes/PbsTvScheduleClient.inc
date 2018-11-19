<?php

/**
 * @file
 * Class with methods for working with the PBS TV Schedule API service.
 */

/**
 * Class PbsTvScheduleClientException.
 */
class PbsTvScheduleClientException extends Exception {}

/**
 * Class PbsTvScheduleClient.
 */
class PbsTvScheduleClient {

  /**
   * Base endpoint.
   *
   * @var string
   */
  const TVSS_PROD = 'https://services.pbs.org/tvss/';

  /**
   * API key provided by PBS.
   *
   * @var string
   */
  private $apiKey;

  /**
   * Station call sign.
   *
   * @var string
   */
  private $callSign;

  /**
   * Whether or not to use the cache for requests with this client.
   *
   * @var bool
   */
  private $useCache;

  /**
   * PbsTvScheduleClient constructor.
   *
   * @param string $apiKey
   *   API key provided by PBS.
   * @param string $callSign
   *   Station call sign.
   * @param bool $useCache
   *   Whether or not to use the cache for requests with this client.
   */
  public function __construct($apiKey = '', $callSign = '', $useCache = TRUE) {
    $this->apiKey = $apiKey;
    $this->callSign = strtolower($callSign);
    $this->useCache = $useCache;
  }

  /**
   * Feed Lookup.
   *
   * There is no actual endpoint for determining feeds. This functions uses the
   * "What's on Today" endpoint and to get feed information.
   *
   * @return array
   *   Feed info from the API.
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getFeeds() {
    $response = $this->get('today');
    $feeds = array();
    foreach ($response['feeds'] as $feed) {
      unset($feed['listings']);
      $feeds[$feed['short_name']] = $feed;
    }
    drupal_alter('pbs_tv_schedule_feeds', $feeds);
    return $feeds;
  }

  /**
   * Channel Lookup / Channel Lookup by Zipcode.
   *
   * @param null|string $zip
   *   (optional) Limit results to a specific zipcode.
   *
   * @return array
   *   Channel info from the API.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-ChannelLookup
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-ChannelLookupbyZipcode
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getChannels($zip = NULL) {
    $uri = 'channels';
    if (!empty($zip)) {
      $uri = $uri . "/zip/" . $zip;
    }
    $response = $this->get($uri);
    // Remove containing "headends" array.
    $channels = [];
    if (isset($response['headends'])) {
      $channels = $response['headends'];
    }
    drupal_alter('pbs_tv_schedule_channels', $channels);
    return $channels;
  }

  /**
   * What's on Today.
   *
   * @param null|string $feed_short_name
   *   If provided, only return the listings for a specific feed by
   *   "short name".
   *
   * @return array
   *   Listing info for today from the API.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-What'sonToday
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getToday($feed_short_name = NULL) {
    $response = $this->get('today');
    $listings = [];
    // Reorganize feed data by "short name".
    foreach ($response['feeds'] as $feed) {
      $listings[$feed['short_name']] = $feed;
    }
    drupal_alter('pbs_tv_schedule_today', $listings);
    if (!empty($feed_short_name) && isset($listings[$feed_short_name])) {
      return $listings[$feed_short_name];
    }
    else {
      return $listings;
    }
  }

  /**
   * Full Listings for a Day.
   *
   * @param string $date
   *   The date to get listings for, in the format YYYYMMDD.
   * @param null|string $feed_short_name
   *   If provided, only return the listings for a specific feed by
   *   "short name".
   *
   * @return array
   *   Listing info for the date from the API.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-FullListingsforaDay
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getFullDay($date, $feed_short_name = NULL) {
    $string = "day/" . $date;
    $response = $this->get($string);
    $listings = [];
    // Reorganize feed data by "short name".
    foreach ($response['feeds'] as $feed) {
      $listings[$feed['short_name']] = $feed;
    }
    drupal_alter('pbs_tv_schedule_full_day', $listings, $date);
    if (!empty($feed_short_name) && isset($listings[$feed_short_name])) {
      return $listings[$feed_short_name];
    }
    else {
      return $listings;
    }
  }

  /**
   * Show information.
   *
   * @param string $show_id
   *   The ID of the show to get information for.
   *
   * @return array
   *   Show info from the API response.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-ShowInformation
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getShowInfo($show_id) {
    $response = $this->get('upcoming/show/' . $show_id);
    drupal_alter('pbs_tv_schedule_show_info', $response);
    return $response;
  }

  /**
   * Program information.
   *
   * @param string $program_id
   *   The ID of the program to get information for.
   *
   * @return array
   *   Program info from the API response.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-ProgramInformation
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getProgramInfo($program_id) {
    if (strpos($program_id, 'onetimeonly') !== FALSE) {
      $string = "upcoming/show/" . $program_id;
    }
    elseif (strpos($program_id, 'movie') !== FALSE) {
      $string = "upcoming/show/" . $program_id;
    }
    else {
      $string = "upcoming/program/" . $program_id;
    }
    $response = $this->get($string);
    drupal_alter('pbs_tv_schedule_program_info', $response);
    return $response;
  }

  /**
   * Program list.
   *
   * Gets a full list of programs and associated data.
   *
   * @return array
   *   Programs from the API response.
   *
   * @url https://docs.pbs.org/display/tvsapi/TV+Schedule+Methods#TVScheduleMethods-StaticListofPrograms
   *
   * @throws \PbsTvScheduleClientException
   */
  public function getPrograms() {
    $response = $this->get('programs', FALSE);
    $programs = $response['programs'];
    drupal_alter('pbs_tv_schedule_programs', $programs);
    return $programs;
  }

  /**
   * Make a GET request to an API endpoint.
   *
   * @param string $endpoint
   *   The endpoint to hit.
   * @param bool $include_call_sign
   *   Whether or not to include the configured callsign in the endpoint URI.
   *
   * @return array|bool
   *   An array of response data or FALSE on error.
   *
   * @throws \PbsTvScheduleClientException
   */
  private function get($endpoint, $include_call_sign = TRUE) {
    $data = [];
    $error = [];

    $cid = 'pbs_tv_schedule_' . str_replace('/', '_', $endpoint);
    if ($this->useCache) {
      if ($cache = cache_get($cid)) {
        return $cache->data;
      }
    }

    $base = self::TVSS_PROD;
    if ($include_call_sign) {
      $base .= $this->callSign . '/';
    }

    $response = drupal_http_request($base . $endpoint . '/', [
      'method' => 'GET',
      'headers' => ['X-PBSAUTH' => $this->apiKey],
    ]);

    if (isset($response->error)) {
      $error = [
        'type' => 'pbs_tv_schedule',
        'message' => 'PBS TV Schedules API GET request failed. Endpoint: 
          @endpoint, error code: @code, message: @message, data: @data.',
        'variables' => [
          '@endpoint' => $endpoint,
          '@code' => $response->code,
          '@message' => $response->error,
          '@data' => $response->data,
        ],
        'severity' => WATCHDOG_CRITICAL,
      ];
    }
    else {
      $data = json_decode($response->data, TRUE);
    }

    if (!empty($error)) {
      watchdog(
        $error['type'],
        $error['message'],
        $error['variables'],
        $error['severity']
      );
      throw new PbsTvScheduleClientException();
    }

    drupal_alter('pbs_tv_schedule_api_response_raw', $data, $endpoint);

    cache_set($cid, $data, 'cache', time() + 86400);

    return $data;
  }

}
