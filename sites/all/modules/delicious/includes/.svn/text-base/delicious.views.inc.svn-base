<?php
// $Id: delicious.views.inc,v 1.1.2.1 2009/01/23 20:24:41 paulbooker Exp $
/**
 * @file
 * Provide views data and handlers for delicious.module
 */

/**
 * @defgroup views_delicious_module delicious.module handlers
 *
 * Includes the ability to create views of just the delicious data.
 * @{
 */

/**
* Implementation of hook_views_handlers() to register all of the basic handlers
* views uses.
*/
function delicious_views_handlers() {
 return array(
   'info' => array(
     'path' => drupal_get_path('module', 'delicious') .'/includes',
     ),
   'handlers' => array(
     'delicious_views_handler_field_description' => array(
       'parent' => 'views_handler_field_url',
     ),
     'delicious_views_handler_field_tag' => array(
       'parent' => 'views_handler_field_prerender_list',
     ),
   ),
 );
}

/**
 * Implementation of hook_views_data()
 */
function delicious_views_data() {
  // Basic table information.

  $data['delicious_link']['table']['group']  = t('Delicious');

  $data['delicious_link']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Delicious link'),
    'help' => t('Stores links from Delicious.com.'),
  );

  $data['delicious_link']['linktime'] = array(
    'title' => t('Posted time'),
    'help' => t('The time the link was first posted.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['delicious_link']['href'] = array(
    'title' => t('Link URL'),
    'help' => t('The href of the link.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['delicious_link']['description'] = array(
    'title' => t('Title'),
    'help' => t('The short description of the link.'),
    'field' => array(
      'handler' => 'delicious_views_handler_field_description',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['delicious_link']['extended'] = array(
    'title' => t('Extended description'),
    'help' => t('The extended description of the link.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['delicious_link']['synced'] = array(
    'title' => t('Sync status'),
    'help' => t('Whether the post in question has been synced with the copy on Delicious.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Delicious post shard status
  $data['delicious_link']['shared'] = array(
    'title' => t('Shared'),
    'help' => t('Whether the post in question is shared or private.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );



  $data['delicious_tag']['table']['group']  = t('Delicious');

  $data['delicious_tag']['table']['join'] = array(
    'delicious_link' => array(
      'left_field' => 'lid',
      'field' => 'lid',
    ),
  );
  $data['delicious_tag']['name'] = array(
    'title' => t('Tag'),
    'help' => t('A tag associated with the item.'),
    'field' => array(
      'handler' => 'delicious_views_handler_field_tag',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['delicious_user']['table']['group']  = t('Delicious');

  $data['delicious_user']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'delicious_link' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Delicious account description
  $data['delicious_user']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The UID of the Delicious account.'),
  );

  // Delicious user name
  $data['delicious_user']['user'] = array(
    'title' => t('User name'),
    'help' => t('The user name of the Delcicious account.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['delicious_user']['linktime'] = array(
    'title' => t('Last updated'),
    'help' => t("The last time this user's links were retrieved."),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}