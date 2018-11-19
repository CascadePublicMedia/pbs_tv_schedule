/**
 * @file
 * Javascript functions for the PBS TV Schedule module.
 */

(function ($, Drupal) {

  'use strict';

  /**
   * Toggle details on a date schedule item.
   */

  Drupal.behaviors.pbsTvScheduleDateItemToggle = {
    attach: function (context, settings) {
      $('.pbs-tv-schedule-schedule-date-item .schedule-item-header', context).once().click(function () {
        $(this).next().slideToggle();
      });
    }
  };

  /**
   * Toggle details on a weekly schedule item and keep details popup on screen.
   */

  Drupal.behaviors.pbsTvScheduleWeekItemToggle = {
    attach: function (context, settings) {
      $('.pbs-tv-schedule-schedule-week-container .schedule-item', context).once().click(function (e) {
        var $schedule_container = $('.pbs-tv-schedule-schedule-week-container');
        var $details_container = $('.schedule-item-details-container');
        var $contents = $('.schedule-item-details-contents');

        // Add contents from clicked element.
        $contents.html(($(this).html()));
        $contents.children().show();

        // If the container is not fixed, make sure the popup displays stays on
        // screen within the schedule container.
        var $position = $details_container.css('position');
        if ($position !== 'fixed') {
          $details_container.css({left: $schedule_container.scrollLeft()});
          $schedule_container.scroll(function () {
            $details_container.css({left: $schedule_container.scrollLeft()});
          });
        }

        // Display the popup.
        $details_container.fadeIn();
        $details_container.click(function () {
          $schedule_container.unbind('scroll');
          $details_container.fadeOut();
        });

        // Prevent the click that triggered this event from closing the popup.
        e.stopPropagation();
      });
    }
  };

  /**
   * Update the URL for a schedule page when the form changes.
   */

  Drupal.ajax.prototype.commands.pbsTvScheduleUpdateScheduleUri = function (ajax, response, status) {
    var $param_string = '?';
    ['channel', 'date', 'program'].forEach(function (param) {
      if (typeof response.values[param] !== 'undefined'
        && response.values[param]) {
        $param_string += param + '=' + response.values[param] + '&';
      }
    });
    $param_string = $param_string.substring(0, $param_string.length - 1);

    window.history.pushState({}, null, window.location.pathname + $param_string);
  };

}(jQuery, Drupal));
