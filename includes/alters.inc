<?php

/**
 * @file
 * Include file for the alter related functions.
 */

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function paragraphs_columns_theme_suggestions_paragraph_alter(&$suggestions, $variables) {

  // Get the information.
  $entity = $variables['elements']['#paragraph'];
  $sanitized_view_mode = strtr($variables['elements']['#view_mode'], '.', '_');
  $type = $entity->getType();

  // Add the suggestions.
  $suggestions[] = 'paragraph__paragraphs_columns';
  $suggestions[] = 'paragraph__paragraphs_columns__' . $type;
  $suggestions[] = 'paragraph__paragraphs_columns__' . $type . '__' . $sanitized_view_mode;
}

/**
 * Implements hook_theme_registry_alter().
 */
function paragraphs_columns_theme_registry_alter(&$theme_registry) {

  $module_path = drupal_get_path('module', 'paragraphs_columns');
  $template_objects = drupal_find_theme_templates($theme_registry, '.html.twig', $module_path);
  $paragraph_types = _paragraphs_columns_get_paragraph_types();

  // 1. Loop through the paragraph types
  // 2. Check if each paragraph exists in the `$template_objects` array
  // 3. If it doesn't exist, remove it from the registry so we don't get any
  // errors.
  foreach ($paragraph_types as $type) {
    $template = 'paragraphs_columns__' . $type;
    if (!isset($template_objects[$template])) {
      unset($theme_registry['paragraphs_columns__' . $type]);
    }
  }

  // Change the field templates directory.
  $theme_registry['field']['path'] = $module_path . '/templates/field';
}
