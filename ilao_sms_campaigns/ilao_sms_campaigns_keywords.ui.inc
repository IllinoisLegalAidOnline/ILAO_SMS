<?php

/**
 * Custom form for campaign keywords.
 *
 * @param $form
 * @param $form_state
 * @param $id
 * @return mixed
 */
function ilao_sms_campaigns_keyword_form($form, &$form_state, $id) {
  if (!empty($id)) {
    $entity = entity_load_single('ilao_sms_keyword',$id);
     $form['is_new'] = array(
      '#type' => 'value',
      '#value' => FALSE,
    );
    $form['id'] = array(
      '#type' => 'value',
      '#value' => $id,
    );
  }
  else {
    $form['is_new'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );

  }
  $form['#validate'][] = 'ilao_sms_campaigns_keyword_validate';

  $form['keyword'] = array (
    '#type' => 'textfield',
    '#title' => t('Keyword'),
    '#description' => t('This is the term a user will text in to receive the related response. Each keyword must be 
      unique.  Keywords are not case sensitive. The following are restricted and can not be used: @keywords', array(
        '@keywords' => strtolower(variable_get('ilao_sms_restricted_keywords')),
    )),
    '#required' => TRUE,
    '#default_value' => isset($entity->keyword) ? $entity->keyword : '',
  );
  $form['campaign'] = array(
    '#type' => 'select',
    '#title'=> t('Campaign'),
    '#required' => TRUE,
    '#options' => ilao_sms_campaigns_load_active_campaigns(),
    '#default_value' => isset($entity->entity_id) ? $entity->entity_id : '',
  );

  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#required' => TRUE,
    '#options' => array (
      'en' => 'English',
      'es' => 'Spanish',
    ),
    '#default_value' => isset($entity->language) ? $entity->language : 'en',
  );
  $form['message_type'] = array (
    '#type' => 'radios',
    '#title' => t('Type of response to send'),
    '#required' => TRUE,
    '#options' => array (
      'node' => 'Legal content',
      'text' => 'Text'
    ),
    '#default_value' => isset($entity->message_type) ? $entity->message_type : '',
    '#description' => t('Selecting "text" will allow you to enter a message to send to 
    the user; selecting "legal content" will allow you to pick an article to send.
    <strong>If you need the user to respond with a keyword, use the text type.</strong>
    '),
  );
  $form['node'] = array(
    '#type' => 'select',
    '#title' => t('Legal content to deliver'),
    '#options' =>  ilao_sms_campaigns_load_legal_content_autocomplete(),
    '#states' => array (
      'visible' => array(
        ':input[name="message_type"]' => array('value' => 'node'),
      ),
      'required' => array (
        ':input[name="message_type"]' => array('value' => 'node'),
      )
    ),
    '#default_value' => isset($entity->nid) ? $entity->nid : 0,
    '#chosen' => TRUE,
  );
  $form['node_type'] = array(
    '#type' => 'radios',
    '#title' => t('Content delivery'),
    '#options' =>  array (
      'link' => t('Send as link.  This will send a shortened url. '),
      'text' => t('Send full text.  This will send the title and body of the content.'),
    ),
    '#description' => t('For long content, we recommend sending as a link. 
     Use the prefix or suffix to add additional text before or after the content/link.
     If full text is selected but the content type is not supported, it will be sent as a link. 
      Only text, process, and bundle overview content can be sent as full text.'),
    '#states' => array (
      'visible' => array(
        ':input[name="message_type"]' => array('value' => 'node'),
      ),
      'required' => array (
        ':input[name="message_type"]' => array('value' => 'node'),
      )
    ),
    '#default_value' => isset($entity->node_content_type) ? $entity->node_content_type : '',
  );
  $form['node_prefix'] = array(
    '#type' => 'textarea',
    '#title' => t('Prefix'),
    '#description' => t('Enter any text you want to be added before the content/link. You can include hyperlinks by pasting the link (no html) in the text field.'),
    '#required' => FALSE,
    '#states' => array (
      'visible' => array(
        ':input[name="message_type"]' => array('value' => 'node'),
      ),
    ),
    '#default_value' => isset($entity->node_prefix) ? $entity->node_prefix : '',
  );
  $form['node_suffix'] = array(
    '#type' => 'textarea',
    '#title' => t('Suffix'),
    '#description' => t('Enter any text you want to be added before the content/link. You can include hyperlinks by pasting the link (no html) in the text field.'),   '#description' => t('Enter any text you want to be added after the content/link.'),
    '#required' => FALSE,
    '#states' => array (
      'visible' => array(
        ':input[name="message_type"]' => array('value' => 'node'),
      ),
    ),
    '#default_value' => isset($entity->node_suffix) ? $entity->node_suffix : '',
  );
  $form['msg_text_container'] = array(
    '#type' => 'container',
    '#states' => array (
      'visible' => array(
        ':input[name="message_type"]' => array('value' => 'text'),
      ),
    ),
  );
  $form['msg_text_container']['message_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Message text'),
    '#description' => t('Enter the text to send to the user if they enter the above keyword'),
    '#required' => FALSE,
     '#states' => array(
      'required' => array (
        ':input[name="message_type"]' => array('value' => 'text'),
      )
    ),
    '#default_value' => isset($entity->message_text) ? $entity->message_text : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('ilao_sms_campaigns_keyword_submit'),
  );
  if (isset($id)) {
    $form['delete'] = array (
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ilao_sms_campaigns_keyword_submit'),
    );
  }


  return $form;
}

/**
 * Custom validation for campaign keyword form.
 *
 * Requires that keywords be unique.
 * Also handles the validation where #states may not work as expected.
 *
 * @param $form
 * @param $form_state
 */
function ilao_sms_campaigns_keyword_validate($form, &$form_state) {
  if ($form_state['values']['message_type'] == 'node') {
    //test that the node and format are required
    if (empty($form_state['values']['node'])) {
      form_set_error('node',t('Legal content is required'));
    }
    if (empty($form_state['values']['node_type'])) {
      form_set_error('node_type',t('Content delivery is required'));
    }
  }
  if($form_state['values']['message_type'] == 'text') {
    if (empty($form_state['values']['message_text'])) {
      form_set_error('message_text',t('Message text is required'));
    }
  }
  $restricted = ilao_sms_get_restricted_keywords_array();
  if (in_array(strtolower($form_state['values']['keyword']),$restricted)) {
    form_set_error('keyword',t('Reserved words can not be used.'));
  }
  if (is_numeric($form_state['values']['keyword'])) {
    form_set_error('keyword',t('Keywords can not be numeric.'));
  }
  ilao_sms_campaigns_keyword_unique($form_state);
  //check uniqueness of keyword.
}

/**
 * Custom submit function for campaign keywords.
 *
 * @param $form
 * @param $form_state
 */
function ilao_sms_campaigns_keyword_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Delete') {
   $form_state['redirect'] = 'admin/sms/keywords/add';
   ilao_sms_campaigns_keyword_delete_form($form_state);
  }
  else {
    global $user;
    if ($form_state['values']['is_new']) {
      //create the entity
      $values['keyword'] = $form_state['values']['keyword'];
      $values['entity_id'] = $form_state['values']['campaign'];
      $values['entity_type'] = 'ilao_sms_campaign';
      $values['message_type'] = $form_state['values']['message_type'];
      $values['message_text'] = $form_state['values']['message_text'];
      $values['nid'] = $form_state['values']['node'];
      $values['node_content_type'] = $form_state['values']['node_type'];
      $values['uid'] = $user->uid;
      $values['node_prefix'] = $form_state['values']['node_prefix'];
      $values['node_suffix'] = $form_state['values']['node_suffix'];
      $values['language'] = $form_state['values']['language'];
      $keyword = ilao_sms_campaigns_keyword_create($values);
      $keyword->save();

    } else {
      //load the entity and update
      $keyword = entity_load_single('ilao_sms_keyword', $form_state['values']['id']);
      $keyword->keyword = $form_state['values']['keyword'];
      $keyword->entity_id = $form_state['values']['campaign'];
      $keyword->entity_type = 'ilao_sms_campaign';
      $keyword->message_type = $form_state['values']['message_type'];
      $keyword->message_text = $form_state['values']['message_text'];
      $keyword->nid = $form_state['values']['node'];
      $keyword->node_content_type = $form_state['values']['node_type'];
      $keyword->node_prefix = $form_state['values']['node_prefix'];
      $keyword->node_suffix = $form_state['values']['node_suffix'];
      $keyword->language = $form_state['values']['language'];
      $keyword->save();
    }
    drupal_set_message(t('SMS keyword has been saved.'),'status');
    $form_state['redirect'] = 'admin/sms/reporting/campaign-keywords';
  }
}

/**
 * Delete campaign keywords confirmation form.
 * @param $form_state
 */
function ilao_sms_campaigns_keyword_delete_form(&$form_state) {
  if (isset($form_state['values']['id'])) {
    $keyword = entity_load_single('ilao_sms_keyword', $form_state['values']['id']);
    ilao_sms_campaigns_keyword_delete($keyword);
    drupal_set_message(t('The keyword was deleted'), 'status');
  }
}

/**
 * Determines if a keyword is unique.
 *
 * @todo Is this needed given the similar function in ilao_sms_campaigns.module?
 *
 * @param $form_state
 */
function ilao_sms_campaigns_keyword_unique(&$form_state) {
  $id = $form_state['values']['id'];
  if (empty($id)) {
    $id = 0;
  }
  $keyword = $form_state['values']['keyword'];
  $subquery = db_select('ilao_sms_campaign','c');
  $subquery->fields('c',array('campaign_id'));
  $subquery->condition('status',1);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'ilao_sms_keyword')
     ->propertyCondition('keyword',$keyword, '=')
    ->propertyCondition('keyword_id',$id,'!=')
    ->propertyCondition('entity_id',$subquery, 'IN')
    ->propertyCondition('entity_type','ilao_sms_campaign','=')

    // Run the query as user 1.
    ->addMetaData('account', user_load(1));
  $result = $query->execute();
  if (!empty($result)) {
    form_set_error('name',t('This keyword is already in use.  Please enter a different name.'));
  }
}
