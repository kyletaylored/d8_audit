<?php

/**
 * Implementation of hook_drush_command().
 */
function d8_audit_drush_command() {
  $items['d8_audit'] = array(
    'description' => 'Show a report on modules ready for D8.',
    'aliases' => array('d8a'),
    'arguments' => array(
      'module' => '(Optional) Show only the output from this module.',
    ),
  );
  return $items;
}

/**
 * Drush command callback for Cache Audit.
 */
function drush_d8_audit() {
  $results = array();

  $cmd_options = [
    'type' => 'module',
    'status' => 'enabled',
    'no-core' => 1,
    'format' => 'list',
    'quiet' => 1,
  ];

  $results = drush_invoke_process('@self', 'pm-list', null, $cmd_options, ['output' => FALSE]);

  // Prep structures.
  $ready = [];
  $yes = $no = 0;
  $total = count($results['object']);

  foreach ($results['object'] as $module => $info) {

    $tmp_ready = [
      'ready' => '',
      'name' => $module,
      'package' => $info['package'],
      'latest version' => '',
      'extra' => '',
    ];

    $url = "https://updates.drupal.org/release-history/" . $module . "/8.x";
    $xmlstr = _d8_audit_get_xml_from_url($url);
    $xmlobj = new SimpleXMLElement($xmlstr);
    // For ease.
    $json = json_encode($xmlobj);
    $xml = json_decode($json, TRUE);

    // D8 version available.
    if (!isset($xml['error'])) {
      if (!empty($xml['releases'])) {
        // Fix weird XML issue.
        $release = (!empty($xml['releases']['release'][0])) ? $xml['releases']['release'][0] : $xml['releases']['release'];

        $tmp_ready['latest version'] = $release['version'];
        $tmp_ready['extra'] = ($extra = $release['version_extra']) ? $extra : '';
        $tmp_ready['ready'] = '✓';
        $yes++;
      } else {
        $no++;
      }
    } else {
      $no++;
    }

    $ready[$module] = $tmp_ready;
  }

  // Prepare ready count array.
  $rc = [
    ['Ready Status', 'Count'],
    ['Yes', $yes],
    ['No', $no],
    ['Total', $total],
  ];

//  var_dump($ready);
  drush_print_table(['Ready', 'Name', 'Package', 'Latest Version', 'Extra']);
  drush_print(str_pad('', 100, "-"));
  drush_print_table($ready, FALSE);
  drush_print(str_pad('', 100, "-"));
  drush_print("\n");
  drush_print("TOTAL COUNT");
  drush_print_table($rc, TRUE);
}

/**
 * Get XML from URL.
 * @param $url
 *
 * @return mixed
 */
function _d8_audit_get_xml_from_url($url){
  $ch = curl_init();

  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13');

  $xmlstr = curl_exec($ch);
  curl_close($ch);

  return $xmlstr;
}
