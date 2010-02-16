<?php
// $Id$

/**
 * Filter handler.
 */
class views_handler_filter_revision_moderation_in_moderation extends views_handler_filter {
  function admin_summary() { }
  function operator_form() { }

  function query() {
    $node_revisions = $this->ensure_my_table();
    $node = $this->query->ensure_table('node');

    $where_array = array();

    // Unpublished node.
    $where_array[] = "($node.status = 0 AND $node_revisions.vid = $node.vid)";

    // Pending revision.
    $where_array[] = "$node_revisions.vid > $node.vid";

    $where = "(". implode(" OR ", $where_array) .")";
    $this->query->add_where($this->options['group'], $where);
  }
}
