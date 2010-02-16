<?php
// $Id$

/**
 * Field handler.
 */
class views_handler_field_revision_moderation_in_moderation extends views_handler_field_node {
  function construct() {
    parent::construct();
    $this->additional_fields['node_vid'] = array('table' => 'node', 'field' => 'vid');
    $this->additional_fields['node_status'] = array('table' => 'node', 'field' => 'status');
    $this->additional_fields['node_revisions_vid'] = array('table' => 'revision_moderation', 'field' => 'vid');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $node_vid = $values->{$this->aliases['node_vid']};
    $node_status = $values->{$this->aliases['node_status']};
    $node_revisions_vid = $values->{$this->aliases['node_revisions_vid']};
    if ($node_status == 0) {
      $output = t('new content');
    }
    elseif ($node_revisions_vid > $node_vid) {
      $output = t('pending revision');
    }
    return $output;
  }
}
