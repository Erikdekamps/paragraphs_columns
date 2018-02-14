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
    $variables['#attached']['library'][] = 'paragraphs_columns/paragraphs_columns';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function paragraphs_columns_preprocess_paragraph(&$variables) {

  // Add the column width value.
  $paragraph = $variables['elements']['#paragraph'];

  // Set the column width.
  if ($paragraph->hasField('field_column_width')) {
    $column_width = $paragraph->get('field_column_width')->value;
    if (!empty($column_width) && $column_width == 'auto') {
      $column_width = _paragraphs_columns_calculate_column_width($paragraph);
      _paragraphs_columns_set_column_width($variables, $column_width);
    }
  }

  // Add the background color.
  if ($paragraph->hasField('field_background_color')) {
    $field = $paragraph->get('field_background_color');
    $color = $field->value;
    if (!empty($color)) {
      _paragraphs_columns_set_background_color($variables, $color);
    }
  }

  // Add the background color.
  if ($paragraph->hasField('field_text_color')) {
    $field = $paragraph->get('field_text_color');
    $color = $field->value;
    if (!empty($color)) {
      _paragraphs_columns_set_text_color($variables, $color);

    }
  }

  // Add the attributes to the row paragraphs.
  if ($paragraph->bundle() == 'row') {
    _paragraphs_columns_add_row_attributes($variables, $paragraph);
  }
}
