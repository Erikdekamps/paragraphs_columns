<?php

/**
 * @file
 * Include file for the processing related functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function paragraphs_columns_preprocess_node(&$variables) {

  // Attach the bootstrap grid.
  if ($variables['node']->getType() === 'paragraphed_page') {
    $variables['#attached']['library'][] = 'paragraphs_columns/bootstrap.grid';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function paragraphs_columns_preprocess_paragraph(&$variables) {

  // Add the column width value.
  $paragraph = $variables['elements']['#paragraph'];
  if ($paragraph->hasField('field_column_width')) {
    $column_width = $paragraph->get('field_column_width')->value;
    if (!empty($column_width) && $column_width == 'auto') {
      $column_width = _paragraphs_columns_calculate_column_width($paragraph);
    }
    $variables['column_width'] = 'col-md-' . $column_width;
  }
}
