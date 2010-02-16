<?php
// $Id$

/**
 * Filter handler.
 */
class views_handler_filter_revision_moderation_state extends views_handler_filter_in_operator {
  function get_value_options() {
    $options = array(
      'current' => t('Current revision'),
      'pending' => t('Pending revision'),
      'old'     => t('Old revision'),
    );
    $this->value_title = t('Revision state');
    $this->value_options = $options;
  }

  function query() {
    $node_revisions = $this->ensure_my_table();
    $node = $this->query->ensure_table('node');

    $where_array = array();
    foreach ($this->value as $value) {
      switch ($value) {
        case 'current':
          $where_array[] = "$node_revisions.vid = $node.vid";
          break;

        case 'pending':
          $where_array[] = "$node_revisions.vid > $node.vid";
          break;

        case 'old':
          $where_array[] = "$node_revisions.vid < $node.vid";
          break;
      }
    }

    switch ($this->operator) {
      case 'in':
        $where = "(". implode(" OR ", $where_array) .")";
        break;

      case 'not in':
        $where = "!(". implode(" OR ", $where_array) .")";
        break;
    }

    $this->query->add_where($this->options['group'], $where);
  }
}
