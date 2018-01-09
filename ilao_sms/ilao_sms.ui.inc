<?php

/**
 * Custom form for SMS configuration.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */

function ilao_sms_form($form, &$form_state) {
  $form['header'] = array(
    '#markup' => t('Use this form to configure SMS settings'),
    '#type' => 'markup',
  );
  $form['ilao_sms_keyword_not_found'] = array (
    '#type' => 'textarea',
    '#title' => t('Message to send users who enter an invalid keyword'),
    '#default_value' => variable_get('ilao_sms_keyword_not_found'),
    '#required' => TRUE,
  );
  $form['ilao_sms_restricted_keywords'] = array (
    '#type' => 'textarea',
    '#title' => t('Enter restricted keywords, separated by commas'),
    '#default_value' => variable_get('ilao_sms_restricted_keywords'),
    '#required' => TRUE,
  );

  $form['ilao_sms_demo_local'] = array (
    '#type' => 'checkbox',
    '#title' => t('Run in demo mode for ilao.dev.dd'),
    '#default_value'=> variable_get('ilao_sms_demo_local'),
   );
  $form['ilao_sms_demo_dev'] = array (
    '#type' => 'checkbox',
    '#title' => t('Run in demo mode for dev.illinoislegalaid.org'),
    '#default_value'=> variable_get('ilao_sms_demo_dev'),
  );
  $form['ilao_sms_demo_staging'] = array (
    '#type' => 'checkbox',
    '#title' => t('Run in demo mode for staging.illinoislegalaid.org'),
    '#default_value'=> variable_get('ilao_sms_demo_staging'),
  );
  $form['ilao_sms_demo_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Demo telephone number to use'),
    '#description' => t('Enter a telephone number to use for demo mode. To test without sending, enter 15005550001'),
    '#required' => TRUE,
    '#default_value'=> variable_get('ilao_sms_demo_phone'),
  );
  $form['ilao_sms_oas_survey_send'] = array (
    '#type' => 'textfield',
    '#title' => t('Number of days after intake complete to send initial follow up survey'),
    '#required' => TRUE,
    '#default_value' => variable_get('ilao_sms_oas_survey_send'),
  );
  $form['ilao_sms_content_survey_send'] = array (
    '#type' => 'textfield',
    '#title' => t('Number of days after legal content is shared to send follow up survey'),
    '#required' => TRUE,
    '#default_value' => variable_get('ilao_sms_content_survey_send'),
  );
/*
  $form['ilao_test_survey'] = array (
    '#type' => 'textfield',(
    '#title' => 'Survey NID',
  );
 */



  $form['actions']['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('ilao_sms_form_submit'),
  );

  return $form;
}

/**
 * Custom form submit for the sms_form.
 *
 * @param $form
 * @param $form_state
 */
function ilao_sms_form_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['ilao_test_survey'])) {
    global $user;
    $survey = ilao_sms_surveys_create();
    $survey->entity_id = $user->uid;
    $survey->entity_type = 'user';
    $survey->nid = $form_state['values']['ilao_test_survey'];
    $survey->save();
    ilao_sms_surveys_send_survey($form_state['values']['ilao_test_survey'], $survey);
  }
  foreach($form_state['values'] as $key => $value) {
    if (strpos($key, 'ilao_sms') !== FALSE) {
      variable_set($key,$value);
    }
  }
  if (empty($form_state['values']['ilao_sms_demo_phone'])) {
    variable_set('ilao_sms_demo_phone','15005550001');
  }
}
