<?php
// $Id$

/**
 * Implementation of hook_views_data()
 */
function revision_moderation_views_data() {
  $data = array();

  // Basic table information.
  $data['revision_moderation']['table']['group']  = t('Revision moderation');

  // For other base tables, explain how we join
  $data['revision_moderation']['table']['join'] = array(
    // Enable for node view.
    'node' => array(
      'table' => 'node_revisions',
      'left_table' => 'node',
      'field' => 'nid',
      'left_field' => 'nid',
     ),
     // Enable for node revision view.
    'node_revisions' => array(
      'table' => 'node_revisions',
      'field' => 'vid',
      'left_field' => 'vid',
    ),
  );

  $data['revision_moderation']['state'] = array(
    'title' => t('Revision state'),
    'help' => t('State of node revision (pending moderation etc.).'),
    'field' => array(
      'handler' => 'views_handler_field_revision_moderation_state',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_revision_moderation_state',
      'allow empty' => FALSE,
    ),
  );

  $data['revision_moderation']['in_moderation'] = array(
    'title' => t('Node in moderation'),
    'help' => t('Either an unpublished node or a pending revision.'),
    'field' => array(
      'handler' => 'views_handler_field_revision_moderation_in_moderation',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_revision_moderation_in_moderation',
      'allow empty' => FALSE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function revision_moderation_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'revision_moderation') .'/views',
    ),
    'handlers' => array(
      'views_handler_field_revision_moderation_state' => array(
        'parent' => 'views_handler_field_node',
      ),
      'views_handler_filter_revision_moderation_state' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'views_handler_field_revision_moderation_in_moderation' => array(
        'parent' => 'views_handler_field_node',
      ),
      'views_handler_filter_revision_moderation_in_moderation' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}
