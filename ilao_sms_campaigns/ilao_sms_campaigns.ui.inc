<?php
/**
 * Custom form for adding/editing campaigns.
 *
 * @param $form
 * @param $form_state
 * @param $id
 * @return mixed
 */
function ilao_sms_campaigns_campaign_form($form, &$form_state, $id = NULL) {
  if (!empty($id)) {
    $entity = entity_load_single('ilao_sms_campaign',$id);
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


  $form['#validate'][] = 'ilao_sms_campaigns_campaign_validate';
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign name'),
    '#description' => t('Enter the name for this campaign; you will use this name when setting up keywords. 
       Each campaign must have a unique name'),
    '#required' => TRUE,
    '#default_value' => isset($entity->name) ? $entity->name : '',

  );
  $form['status'] = array(
    '#type' => 'radios',
    '#title' => t('Active?'),
    '#required' => TRUE,
    '#options' => array (
      '0' => t('No'),
      '1' => t('Yes'),
    ),
    '#default_value' => isset($entity->status) ? $entity->status : '1',

  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('ilao_sms_campaigns_campaign_submit'),
  );

  return $form;
}

/**
 * Form validation for the campaign form.
 *
 * Ensures that campaign names are unique.
 *
 * @param $form
 * @param $form_state
 */
function ilao_sms_campaigns_campaign_validate($form, &$form_state) {
  $name = $form_state['values']['name'];
  //check for duplicate campaign names
  //use an EFQ
  $id = $form_state['values']['id'];
  if (empty($id)) {
    $id = 0;
  }
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'ilao_sms_campaign')
    ->propertyCondition('status', 1)
    ->propertyCondition('name',$name, '=')
    ->propertyCondition('campaign_id',$id,'!=')

    // Run the query as user 1.
    ->addMetaData('account', user_load(1));
  $result = $query->execute();
  if (!empty($result)) {
    form_set_error('name',t('This campaign name is already in use.  Please enter a different name.'));
  }

}

/**
 * Custom submit handler for campaign form.
 * @param $form
 * @param $form_state
 */
function ilao_sms_campaigns_campaign_submit($form, &$form_state) {
  global $user;
  $form_state['redirect'] = 'admin/sms/keywords/add';

  if ($form_state['values']['is_new']) {
    $values['name'] = $form_state['values']['name'];
    $values['status'] = $form_state['values']['status'];
    $values['uid'] = $user->uid;

    $campaign = ilao_sms_campaigns_create($values);
    $campaign->save();
    drupal_set_message(t('Campaign @name has been created', array('@name' => $values['name'])),'status');
  }
  else {
    $campaign = entity_load_single('ilao_sms_campaign',$form_state['values']['id']);
    $campaign->name = $form_state['values']['name'];
    $campaign->status = $form_state['values']['status'];
    $campaign->save();
    drupal_set_message(t('Campaign @name has been updated', array('@name' => $values['name'])),'status');
  }


}