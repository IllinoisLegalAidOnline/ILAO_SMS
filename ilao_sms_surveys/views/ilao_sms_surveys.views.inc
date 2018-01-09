<?php

function ilao_sms_surveys_views_data_alter(&$data) {

  $data['ilao_sms_surveys']['ilao_sms_surveys_webform'] = array(
    'title' => t('Text Survey Webform Mapping'),
    'help' => t('Relation between submission_id in ilao_sms_surveys with webform sid.'),
    'relationship' => array(
      'base' => 'webform_submissions',
      'base field' => 'sid',
      'relationship field' => 'submission_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Text Survey Webform Mapping'),
    ),
  );
}