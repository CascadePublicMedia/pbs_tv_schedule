<?php

/**
 * @file
 * Date-based schedule item template.
 *
 * Available custom variables:
 * - $feed: Short name of the feed being listed.
 * - $show_id: Show ID from the API.
 * - $start_time: Item start time.
 * - $title: Item title.
 * - $description: Item description.
 * - $subtitle: Item subtitle (e.g. episode title), if one exists.
 * - $parent_description: Parent item description, if one exists.
 * - $duration: Item duration in minutes.
 * - $closed_captions: Boolean indicator for closed captions availability.
 * - $hd: Boolean indicator for HD.
 * - $stereo: Boolean indicator for stereo.
 * - $animated: Boolean indicator for animated items.
 * - $upcoming_url: URL for a listing of upcoming airings of the show.
 *
 * @see template_preprocess_pbs_tv_schedule_schedule_date_item()
 */
?>

<div class="pbs-tv-schedule-schedule-date-item">
  <div class="schedule-item-header">
    <div class="schedule-item-start-time"><?php print $start_time->format('g:i a'); ?></div>
    <div class="schedule-item-title"><?php print $title; ?></div>
  </div>
  <div class="schedule-item-details">
    <div class="schedule-item-metadata">
      <div class="schedule-item-duration">
        <?php if (isset($duration_formatted)): ?>
          <?php print $duration_formatted; ?>
        <?php else: ?>
          <?php print $duration; ?>
        <?php endif; ?>
      </div>
      <div class="schedule-item-icons">
        <?php if (isset($closed_captions_icon)): ?>
          <?php print render($closed_captions_icon); ?>
        <?php endif; ?>

        <?php if (isset($hd_icon)): ?>
          <?php print render($hd_icon); ?>
        <?php endif; ?>

        <?php if (isset($stereo_icon)): ?>
          <?php print render($stereo_icon); ?>
        <?php endif; ?>
      </div>
    </div>
    <div class="schedule-item-description">
      <?php if (!empty($subtitle)): ?>
        <div class="schedule-item-subtitle"><?php print $subtitle ?></div>
      <?php endif; ?>
      <p><?php print $description; ?></p>
      <?php if ($show_id != PBS_TV_SCHEDULE_SHOW_ID_NONE): ?>
        <a
          href="<?php print $upcoming_url ?>"
          data-show-id="<?php print $show_id; ?>"
          class="use-ajax">
          <?php print t('Upcoming Airings') ?>
        </a>
      <?php endif; ?>
    </div>
  </div>
</div>
