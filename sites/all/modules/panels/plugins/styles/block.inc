<?php
// $Id: block.inc,v 1.1.2.5 2009/07/14 18:41:04 merlinofchaos Exp $

/**
 * @file
 * Definition of the 'naked' panel style.
 */

// ---------------------------------------------------------------------------
// Panels hooks.

/**
 * Implementation of hook_panels_style_info().
 */
function panels_block_panels_styles() {
  return array(
    'title' => t('System block'),
    'description' => t('Display the pane as a system block; this is more restrictive than the default.'),
    'render pane' => 'panels_block_style_render_pane',
  );
}

// ---------------------------------------------------------------------------
// Panels style plugin callbacks.

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_block_style_render_pane($content, $pane, $display) {
  if (empty($content->content)) {
    return;
  }

  if (!empty($content->title)) {
    $content->subject = $content->title;
  }

  $content->region = $pane->panel;
  if (!isset($content->module)) {
    $content->module = $content->type;
  }
  if (!isset($content->delta)) {
    $content->delta = $content->subtype;
  }

  return theme('block', $content);
}

