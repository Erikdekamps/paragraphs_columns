<?php

/**
 * @file
 * Include file for the helper functions.
 */

use Drupal\paragraphs\Entity\Paragraph;

/**
 * Helper function to get a list of paragraph types by machine name.
 *
 * @return array
 *   Returns a list of paragraph types by machine name.
 */
function _paragraphs_columns_get_paragraph_types() {
  $paragraph_bundles = \Drupal::service('entity_type.bundle.info')
    ->getBundleInfo('paragraph');
  return array_keys($paragraph_bundles);
}

/**
 * Calculate the column width.
 *
 * @param \Drupal\paragraphs\Entity\Paragraph $paragraph
 *   The paragraph the column is in.
 *
 * @return float
 *   Returns the column width as integer.
 */
function _paragraphs_columns_calculate_column_width(Paragraph $paragraph) {

  // Initialize the starting values.
  $auto_paragraphs = 0;
  $auto_width = 12;

  // Get the wrapper (row) paragraph.
  $pid = $paragraph->get('parent_id')->value;
  $parent_paragraph = Paragraph::load($pid);

  // Check for the columns the parent has.
  if ($parent_paragraph->hasField('field_column')) {
    $columns = $parent_paragraph->get('field_column')->getValue();
    if (!empty($columns)) {

      // Loop through the columns and calculate the width.
      foreach ($columns as $column) {
        $paragraph_column = Paragraph::load($column['target_id']);
        if ($paragraph_column->hasField('field_column_width')) {
          $column_width = $paragraph_column->get('field_column_width')->value;
          $auto_width -= $column_width;
          if ($column_width == 'auto') {
            $auto_paragraphs++;
          }
        }
      }
    }
  }

  // Set the auto width based on the amount of auto width paragraphs.
  $paragraph_width = $paragraph->get('field_column_width')->value;
  $column_width = floor($paragraph_width == 'auto' ? floor($auto_width / $auto_paragraphs) : $paragraph_width);

  // Return the column width.
  return $column_width;
}

/**
 * Set the column width for the paragraph.
 *
 * @param array $variables
 *   The paragraph variables.
 * @param int $column_width
 *   The column width.
 */
function _paragraphs_columns_set_column_width(array &$variables, $column_width) {

  // Set the class for the column width.
  $variables['attributes']['class'] = ['col-md-' . $column_width];
}

/**
 * Add a background color to a paragraph.
 *
 * @param array $variables
 *   The paragraph variables.
 * @param string $color
 *   The color code.
 */
function _paragraphs_columns_set_background_color(array &$variables, $color) {

  // Generate the style.
  $style = 'background-color:#' . $color . ';';

  // Set the attribute.
  $variables['attributes']['style'][] = $style;
}

/**
 * Add a text color to a paragraph.
 *
 * @param array $variables
 *   The paragraph variables.
 * @param string $color
 *   The color code.
 */
function _paragraphs_columns_set_text_color(array &$variables, $color) {

  // Generate the style.
  $style = 'color:#' . $color . ';';

  // Set the attribute.
  $variables['attributes']['style'][] = $style;
}

/**
 * Makes a row full width.
 *
 * @param array $variables
 *   The paragraph variables.
 */
function _paragraphs_columns_set_row_full_width(array &$variables) {

  // Set the attribute.
  $variables['attributes']['class'] = ['row', 'full-width'];
}
