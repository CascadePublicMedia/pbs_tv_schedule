<?php

/**
 * @file
 * Week-based schedule item template.
 *
 * Available custom variables:
 * - $show_id: Show ID from the API.
 * - $title: Item title.
 * - $description: Item description.
 * - $subtitle: Item subtitle (e.g. episode title), if one exists.
 * - $parent_description: Parent item description, if one exists.
 * - $duration: Item duration in minutes.
 * - $closed_captions: Boolean indicator for closed captions availability.
 * - $hd: Boolean indicator for HD.
 * - $stereo: Boolean indicator for stereo.
 * - $animated: Boolean indicator for animated items.
 * - $flex_basis: Flexbox cell basis.
 *
 * @see template_preprocess_pbs_tv_schedule_schedule_week_item()
 */
?>

<div class="schedule-cell schedule-item" style="flex-basis: <?php print $flex_basis; ?>%">
  <div class="schedule-item-title"><?php print $title; ?></div>
  <div class="schedule-item-duration">
    <?php if (isset($duration_formatted)): ?>
      <?php print $duration_formatted; ?>
    <?php else: ?>
      <?php print $duration; ?>
    <?php endif; ?>
  </div>
  <div class="schedule-item-details">
    <?php if (!empty($subtitle)): ?>
      <div class="schedule-item-subtitle"><?php print $subtitle ?></div>
    <?php endif; ?>
    <div class="schedule-item-description"><?php print $description; ?></div>
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
</div>
