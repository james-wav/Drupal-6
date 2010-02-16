<?php 
// $Id: delicious_views_handler_field_description.inc,v 1.1.2.1 2009/01/23 20:24:41 paulbooker Exp $ 
/**
 * Field handler to provide simple renderer that turns a URL into a clickable link.
 */
class delicious_views_handler_field_description extends views_handler_field_url {
  /**
   * Override init function to provide generic option to link to node.
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
    if (!empty($data['display_as_link'])) {
      $this->additional_fields[] = 'href';
    }
  }

  function render($values) {
    $title = check_plain($values->{$this->field_alias});
    if (!empty($this->options['display_as_link'])) {
        return l($title, check_url($values->{$this->table_alias .'_href'}), array('html' => TRUE));
        break;
    }
    else {
      return check_plain($title);
    }
  }
}