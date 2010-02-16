<?php
// $Id$

/**
 * Field handler.
 */
class views_handler_field_revision_moderation_state extends views_handler_field_node {
  function construct() {
    parent::construct();
    $this->additional_fields['node_vid'] = array('table' => 'node', 'field' => 'vid');
    $this->additional_fields['node_revisions_vid'] = array('table' => 'revision_moderation', 'field' => 'vid');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $node_vid = $values->{$this->aliases['node_vid']};
    $node_revisions_vid = $values->{$this->aliases['node_revisions_vid']};
    if (empty($node_vid) || empty($node_revisions_vid)) {
      return $output;
    }

    if ($node_revisions_vid > $node_vid) {
      $output = t('pending revision');
    }
    elseif ($node_revisions_vid < $node_vid) {
      $output = t('old revision');
    }
    else {
      $output = t('current revision');
    }

    return $output;
  }
}
