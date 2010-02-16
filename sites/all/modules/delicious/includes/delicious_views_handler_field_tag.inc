<?php
// $Id: delicious_views_handler_field_tag.inc,v 1.1.2.1 2009/01/23 20:24:41 paulbooker Exp $
class delicious_views_handler_field_tag extends views_handler_field_prerender_list {
  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['lid'] = array('table' => 'delicious_link', 'field' => 'lid');
  }

  function query() {
    $this->add_additional_fields();
  }

  function pre_render($values) {
    $this->field_alias = $this->aliases['lid'];
    $this->items = array();

    $lids = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['lid']})) {
        $lids[] = $result->{$this->aliases['lid']};
      }
    }

    $sql = "SELECT dt.name, dt.lid FROM {delicious_tag} dt WHERE dt.lid IN (". implode(", ", $lids) .")";
    $results = db_query($sql);

    while ($result = db_fetch_array($results)) {
      $this->items[$result['lid']][] = check_plain($result['name']);
    }
  }
}


function delicious_views_data_alter(&$data) {
  $data['users']['table']['join']['delicious_link'] = array(
    'left_table' => 'delicious_user_user',
    'left_field' => 'uid',
    'field' => 'uid',
  );
}