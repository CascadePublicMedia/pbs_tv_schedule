<?php

/**
 * @file
 * Schedule search page template.
 *
 * Available custom variables:
 * - $program: The name of the program being searched.
 * - $items: Array of listing items keyed by text date for headers.
 *
 * @see template_preprocess_pbs_tv_schedule_schedule_search()
 */
?>

<div class="pbs-tv-schedule-schedule-date">
  <?php foreach ($items as $header => $listings): ?>
    <div class="pbs-tv-schedule-schedule-search-header">
      <?php print $header; ?>
    </div>
    <?php print drupal_render($listings); ?>
  <?php endforeach; ?>
</div>
