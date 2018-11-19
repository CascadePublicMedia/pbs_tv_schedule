<?php

/**
 * @file
 * Date-based schedule page template.
 *
 * Available custom variables:
 * - $date: DateTime object for the date being viewed.
 * - $items: Array of all items with render arrays for program cell data.
 * - $items_past: Array of items occurring in the past.
 * - $items_future: Array of items occurring in the future.
 *
 * $items_past and $items_future should only be populated if $date is today.
 *
 * @see template_preprocess_pbs_tv_schedule_schedule_date()
 */
?>

<div class="pbs-tv-schedule-schedule-date">
  <?php if (!empty($items_past) || !empty($items_future)): ?>
    <details class="schedule-items-past">
      <summary><?php print t('Earlier schedule'); ?></summary>
      <?php print drupal_render($items_past); ?>
    </details>
    <div class="schedule-items-future">
      <?php print drupal_render($items_future); ?>
    </div>
  <?php else: ?>
    <?php print drupal_render($items); ?>
  <?php endif; ?>
</div>
