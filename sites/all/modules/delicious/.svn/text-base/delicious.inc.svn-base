<?php
// $Id: delicious.inc,v 1.1.2.2 2009/01/28 23:49:06 paulbooker Exp $
// ----------------------------------------------------------------------------
// REST calls to del.icio.us API
//
function _delicious_make_auth_header($username, $password) {
  $realm = "del.icio.us API";
  $user_agent = "drupal.contributions.delicious.module/1.0";
  $auth = 'Basic '. base64_encode($username .':'. $password);
  $headers = array();
  $headers['User-Agent'] = $user_agent;
  $headers['Authorization'] = $auth; 
  return $headers;
}

/**
 * get a page FROM the delicious API.
 */
function _delicious_get_page($page, $user, $pass) {
  // Force 1 second throttle.
  static $last_hit;
  $now = microtime(TRUE);
  if ($now < $last_hit + 1) {
    sleep(1);
  }
  $last_hit = $now;
  
  return drupal_http_request(DELICIOUS_API_URL . $page,
    _delicious_make_auth_header($user, $pass));
}

/**
 * cron support: update all users who have Delicious Links.
 */
function _delicious_update_user($user) { 
  $resp = _delicious_get_page(DELICIOUS_UPDATE_URL, $user->user, $user->pass);  
  $code = intval($resp->redirect_code ? $resp->redirect_code : $resp->code);
  if ($code != 200) { 
    db_query("UPDATE {delicious_user} SET lastcode = %d WHERE uid=%d", $code, $user->uid);
    return 0;
  }
  else if ($resp->error) { 
    watchdog("error", "delicious response: $resp->error");
  }

  $parser = new _delicious_update_parser();
  $lastupdate = $parser->parse($resp->data);
  if ($lastupdate > $user->lastupdate) { 
    $resp = _delicious_get_page(DELICIOUS_POSTS_URL, $user->user, $user->pass); 
    $code = intval($resp->redirect_code ? $resp->redirect_code : $resp->code);
    if ($code != 200) {
      db_query("UPDATE {delicious_user} SET lastcode = %d WHERE uid=%d", $code, $user->uid);
      return 0;
    }
    $parser = new _delicious_post_parser($user->uid);
    $parser->parse($resp->data);
    db_query("UPDATE {delicious_user} SET lastcode = %d, lastupdate = '%s' WHERE uid=%d", $code, $lastupdate, $user->uid);
    return 1;

  }
  return 0;
}

// ----------------------------------------------------------------------------
// XML parsing objects
//
// If another object gets created, refactor some of the code into a base object
// and inherit

//
// parse the update string
//
class _delicious_update_parser {

  function parse($data) {
    $this->update = 0;
    $this->xml_parser = drupal_xml_parser_create($data);
    xml_set_object($this->xml_parser, $this);
    xml_set_element_handler($this->xml_parser, "start_element", "end_element");

    if (!xml_parse($this->xml_parser, $data)) {
      watchdog("warning", sprintf("XML error: %s at line %d",
        xml_error_string(xml_get_error_code($this->xml_parser)),
        xml_get_current_line_number($this->xml_parser)));
    }

    xml_parser_free($this->xml_parser);
    return $this->update;
  }

  function start_element($parser, $name, $attrs) {
    if ($name == 'UPDATE') {
      if ($attrs["TIME"] != '') {
        $this->update = _delicious_date_parse($attrs["TIME"]);
      }
    }
  }

  function end_element($parser, $name) {
  }

}

//
// parse all posts, and write them to the database; delete all unsynced
// posts for that user.
//
class _delicious_post_parser {

  function _delicious_post_parser($uid = 0) {
    $this->uid = $uid;
  }

  function parse($data) {
    // unsync all related records
    db_query("UPDATE {delicious_link} SET synced=0 WHERE uid=%d", $this->uid);
    db_query("UPDATE {delicious_tag} SET synced=0 WHERE uid=%d", $this->uid);
    $this->xml_parser = drupal_xml_parser_create($data);
    xml_set_object($this->xml_parser, $this);
    xml_set_element_handler($this->xml_parser, "start_element", "end_element");

    if (!xml_parse($this->xml_parser, $data)) {
      watchdog("warning", sprintf("XML error: %s at line %d",
        xml_error_string(xml_get_error_code($this->xml_parser)),
        xml_get_current_line_number($this->xml_parser)));
    }

    xml_parser_free($this->xml_parser);
    // delete all unsynced records
    db_query("DELETE FROM {delicious_link} WHERE synced=0 and uid=%d", $this->uid);
    db_query("DELETE FROM {delicious_tag} WHERE synced=0 and uid=%d", $this->uid);
  }

  function start_element($parser, $name, $attrs) {
    if (!isset($attrs["SHARED"]) && ($attrs["DESCRIPTION"] != '')) {
      $desc = db_escape_string(utf8_decode($attrs["DESCRIPTION"]));
      $href = db_escape_string($attrs["HREF"]);
      $tags = split(' ', $attrs["TAG"]);
      if ($attrs["EXTENDED"] != '') {
        $extended = db_escape_string($attrs["EXTENDED"]);
      }
      $hash = $attrs["HASH"];
      $time = _delicious_date_parse($attrs["TIME"]); // yay we gotta parse this don't we?

      $obj = db_fetch_object(db_query("SELECT * FROM {delicious_link} WHERE hash='%s'", $hash));
      if ($obj) {
        db_query("UPDATE {delicious_link} SET synced=1, description='%s', extended='%s', href='%s', linktime='%s' WHERE hash='%s'", $desc, $extended, $href, $time, $hash);
        foreach ($tags as $tag) {
          $tagobj = db_fetch_object(db_query("SELECT * FROM {delicious_tag} WHERE lid = %d and name = '%s'", $obj->lid, $tag));
          if ($tagobj) {
            db_query("UPDATE {delicious_tag} SET synced=1 WHERE lid=%d and name='%s'", $obj->lid, $tag);
          }
          else {
            db_query("INSERT INTO {delicious_tag} (lid, uid, name, synced) VALUES (%d, %s, '%s', 1)", $obj->lid, $this->uid, $tag);
          }
        }
      }
      else {
        db_query("INSERT INTO {delicious_link} (lid, uid, href, description, extended, linktime, hash, synced) VALUES (%d, %d, '%s', '%s', '%s', %d, '%s', 1)", NULL, $this->uid, $href, $desc, $extended, $time, $hash);
        $lid = db_last_insert_id("delicious_link", "lid");

        foreach ($tags as $tag) {
          db_query("INSERT INTO {delicious_tag} (lid, uid, name, synced) VALUES (%d, %d, '%s', 1)", $lid, $this->uid, $tag);
        }
      }
    }
  }

  function end_element($parser, $name) {
  }
}

// ----------------------------------------------------------------------------
// smart/crosslinking stuff and general support

//
// render a link to the node's first term if present for crosslinking
//
function _delicious_term_link(&$node) {
  $terms = taxonomy_node_get_terms($node->nid);
  $term = array_shift($terms);
  if (!empty($term->name)) {
    $tag = strtolower(str_replace(' ', '', $term->name));
    return DELICIOUS_BASE_URL ."tag/$tag";
  }
}

//
// smart-tagging support
//
function _delicious_tag_string($text, $tags, $username) {

  if (!$tags) {
    return $text;
  }
  // Match absolute URLs.
  $url_regex = '((http://|https://|ftp://|mailto:|smb://|afp://|file://|gopher://|news://|ssl://|sslv2://|sslv3://|tls://|tcp://|udp://)([a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&=/;-]))';
  // Match e-mail addresses.
  $mail_regex = '([A-Za-z0-9._-]+@[A-Za-z0-9._+-]+\.[A-Za-z]{2,4})';
  // Match www domains/addresses.
  $www_regex = '(www\.[a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+~#\&=/;-])';

  // Replace all URLs, Domains, and e-mail address with tokens.
  $i = 1;
  $replacements = array();
  while (preg_match("`($url_regex|$mail_regex|$www_regex)`i", $text, $matches)) {
    $token = '__delicious_processing_replacement_'. $i++;
    $replacements[$token] = $matches[1];
    $text = str_replace($matches[1], $token, $text);
  } 
  // error, it must start with a tag... :-(
  foreach ($tags as $tag) { 
    if (!empty($tag) && $tag != ' ') {
      $path = DELICIOUS_BASE_URL . urlencode($username) .'/'. urlencode($tag);
      $modulepath = drupal_get_path('module', 'delicious');
      $delicious_icon = theme('image', $modulepath .'/deliciousIcon.gif', '', t('Browse @username\'s delicious \'@tag\' tagged links', array('@username' => $username, '@tag' => $tag), '', array('class' => 'delicious-icon')));
	  $delicious_link = l($delicious_icon, $path, array('html' => TRUE));
	 

      $tag = preg_quote($tag);
      if (!preg_match('/<.+>/', $text)) {
        $text = preg_replace('/(\b'. $tag .'\b)/i', '$1'. $delicious_link, $text);
      }
      else {
        $text = preg_replace('/(?<=>)([^<]+)?(\b'. $tag .'\b)/i', '$1$2'. $delicious_link, $text);
      }
    }
  }
  // Restore all URLs, Domains, and e-mail addresses.
  foreach ($replacements as $token => $match) {
    $text = str_replace($token, $match, $text);
  }
  return $text;
}

//
// support function for tagged text
//
function _delicious_tag_text($text, $name) {
  $result = db_query("SELECT distinct(name) FROM {delicious_tag}");
  while ($tag = db_fetch_object($result)) {
    $tags[] = $tag->name;
  }
  return _delicious_tag_string($text, $tags, $name);
}

//
// General configuration support
//
function _delicious_nodetype_applicable($type) {
  $del = variable_get('delicious_node_types', array('blog', 'story', 'page'));
  if (is_array($del)) {
    return in_array($type, $del);
  }
}

// Translate delicious dates into normal dates
function _delicious_date_parse($date) {
    $date = str_replace('T', ' ', $date);
    $date = str_replace('Z', ' ', $date);
    return strtotime($date);
}