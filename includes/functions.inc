<?php

/**
 * @file
 * Include file for the helper functions.
 */

use Drupal\Core\Template\Attribute;
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
 * Create the row attributes.
 *
 * @param array $variables
 *   The paragraph variables.
 * @param \Drupal\paragraphs\Entity\Paragraph $paragraph
 *   The paragraph the column is in.
 */
function _paragraphs_columns_add_row_attributes(array &$variables, Paragraph $paragraph) {

  // Set the main section attributes.
  $variables['attributes']['class'][] = 'paragraph-container';

  // Attribute object for the form container.
  $container_attributes = new Attribute();
  $container_attributes['class'] = ['container'];

  // Check for full width.
  if ($paragraph->hasField('field_full_width') && $paragraph->get('field_full_width')->value) {
    $variables['attributes']['class'][] = 'full-width';
  }

  // Check for full width on the content.
  if ($paragraph->hasField('field_fluid') && $paragraph->get('field_fluid')->value) {
    $container_attributes['class'] = ['container-fluid'];
  }

  // Set the container attributes.
  $variables['container_attributes'] = $container_attributes;

  // Attribute object for the form row.
  $row_attributes = new Attribute();
  $row_attributes['class'] = ['row'];

  // Set the row attributes.
  $variables['row_attributes'] = $row_attributes;
}
