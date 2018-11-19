<?php

/**
 * @file
 * Schedule week page template.
 *
 * Available custom variables:
 * - $title: Week title text.
 * - $link_previous: Render array for a link to last week's schedule.
 * - $link_next: Render array for a link to next week's schedule.
 * - $headers: Array of headers for the first line of the schedule.
 * - $rows: Array of rows with render arrays for program cell data.
 *
 * @see template_preprocess_pbs_tv_schedule_schedule_week()
 */
?>

<div class="pbs-tv-schedule-schedule-week">
  <div class="schedule-title">
    <?php if (!empty($link_previous)): ?>
      <div class="schedule-link-previous">
        <?php print drupal_render($link_previous); ?>
      </div>
    <?php endif; ?>
    <?php print $title ?>
    <?php if (!empty($link_next)): ?>
      <div class="schedule-link-next">
        <?php print drupal_render($link_next); ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="pbs-tv-schedule-schedule-week-container">
    <div class="schedule-item-details-container">
      <div class="schedule-item-details-contents"></div>
    </div>
    <div class="schedule-row">
      <?php foreach ($headers as $header): ?>
        <div class="schedule-cell schedule-column-header"><?php print $header; ?></div>
      <?php endforeach; ?>
    </div>
    <?php foreach ($rows as $row): ?>
      <div class="schedule-row">
        <?php print drupal_render($row); ?>
      </div>
    <?php endforeach; ?>
  </div>
</div>
