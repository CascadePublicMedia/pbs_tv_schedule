PBS TV Schedule
===============

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Templates
 * Hooks
 * Functionality
 * Maintainers
 * License

INTRODUCTION
------------

PBS TV Schedule uses the [TV Schedules API](https://docs.pbs.org/display/tvsapi)
to provide a simple, themeable daily/weekly schedule view for PBS member
station websites.

 * For a full description of the module, visit the project page:
   [PBS TV Schedule](https://www.drupal.org/project/pbs_tv_schedule)
   
 * To submit bug reports and feature suggestions, or to track changes:
   [PBS TV Schedule issues](https://www.drupal.org/project/issues/pbs_tv_schedule)

REQUIREMENTS
------------

[TV Schedules API](https://docs.pbs.org/display/tvsapi) credentials (provided by 
PBS)are required to use this module.

 * For information about how to obtain credentials, see:
   [TV Schedules Service (TVSS) API - Access](https://docs.pbs.org/display/tvsapi#TVSchedulesService(TVSS)API-Access)

INSTALLATION
------------

Install as you would normally install a contributed Drupal module. See
[Installing modules](https://www.drupal.org/docs/7/extend/installing-modules)
for further information.

CONFIGURATION
-------------

Configure user permissions in `Administration » People » Permissions`:

 * `Administer PBS TV Schedule`

   Users need this permission to access and configure the PBS TV Schedule 
   module's settings.

Module configure is found in `Configuration » System » PBS TV Schedule`:

 * `Station Call Sign`
 
   Station call sign to use when retrieving schedule data.
   
 * `API Key`
  
   Secret API key as provided by PBS. See **REQUIREMENTS** for more information.
   
 * `Feeds Configuration`
  
   These options will be available after a valid Station Call Sign and API Key 
   have been provided. Feeds can be sorted and enabled/disabled, and one feed 
   can be set as the default. These settings will apply to feeds select lists
   presented to the user on schedule pages.

TEMPLATES
---------

Eight templates are provided. These templates can be overridden by custom theme
implementations.

 * `pbs-tv-schedule-schedule.tpl.php`
 
   Container for the day view filter form elements.
 
 * `pbs-tv-schedule-schedule-date.tpl.php`
 
   Primary container for the day view page at `/pbs-tv-schedule/schedule`.
 
 * `pbs-tv-schedule-schedule-date-item.tpl.php`
 
   Item details for listings on the day view page.
 
 * `pbs-tv-schedule-schedule-no-results.tpl.php`
 
   "No results" template for the Program title based search on the day view 
   page.
 
 * `pbs-tv-schedule-schedule-search.tpl.php`
 
   Container for the Program title based search on the day view page.
 
 * `pbs-tv-schedule-schedule-week.tpl.php`
 
   Primary container for the week view page at `/pbs-tv-schedule/schedule`.
 
 * `pbs-tv-schedule-schedule-week-filter.tpl.php`
 
   Container for the week view filter form elements.
 
 * `pbs-tv-schedule-schedule-week-item.tpl.php`
 
   Item details for listings on the week view page.
   
HOOKS
-----

The PBS TV Schedule module provides hooks for easier API interaction from other
Drupal modules.

 * `hook_pbs_tv_schedule_api_response_raw_alter()`
 
   Alter an API response before it is cached and modified by other methods.

 * `hook_pbs_tv_schedule_*_alter(`
 
   Alter data from API responses for all getter methods of the 
   `PbsTvScheduleClient` class.
   
    * `channels_alter`: `getChannels`
    * `feeds_alter`: `getFeeds`
    * `full_day_alter`: `getFullDay`
    * `program_info_alter`: `getProgramInfo`
    * `programs_alter`: `getPrograms`
    * `show_info_alter`: `getShowInfo`
    * `today_alter`: `getToday`

 * `hook_pbs_tv_schedule_listing_alter()`
 
   Alter information for a single listing item.

FUNCTIONALITY
-------------

With a valid call sign and API key (see **CONFIGURATION**), this module provides
two pages:

 * `Day view: /pbs-tv-schedule/schedule`
 
   Single day listing of shows with time, title, episode and upcoming airings
   information. Users can filter by a specific day, feed ("Channel"), or Program
   name.
 
 * `Week view: /pbs-tv-schedule/schedule/week`
 
   Full week schedule information organized in a horizontal view by date and 
   time of day. Users can click on a specific block to see additional listing
   information.
      
MAINTAINERS
-----------

Current maintainers:
 * Christopher Charbonneau Wells (wells) - https://www.drupal.org/u/wells

This project is sponsored by:
 * [Cascade Public Media](https://www.drupal.org/cascade-public-media) for 
 [KCTS9.org](https://kcts9.org/) and [Crosscut.com](https://crosscut.com/).
 
LICENSE
-------

All code in this repository is licensed 
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html). A LICENSE file is not 
included in this repository per Drupal's module packaging specifications.

See [Licensing on Drupal.org](https://www.drupal.org/about/licensing).
