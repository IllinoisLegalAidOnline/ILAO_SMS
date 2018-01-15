<?php
/**
 * @file
 * ilao_sms_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ilao_sms_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'campaign_keywords';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ilao_sms_keyword';
  $view->human_name = 'Campaign Keywords';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Campaign Keywords';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Text campaign keywords: Campaign */
  $handler->display->display_options['relationships']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['relationships']['entity_id']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['relationships']['entity_id']['field'] = 'entity_id';
  /* Field: Text campaign keywords: Message type */
  $handler->display->display_options['fields']['message type']['id'] = 'message type';
  $handler->display->display_options['fields']['message type']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['message type']['field'] = 'message type';
  /* Field: Text campaigns: Campaign name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'ilao_sms_campaign';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'entity_id';
  /* Field: Text campaign keywords: ID */
  $handler->display->display_options['fields']['keyword_id']['id'] = 'keyword_id';
  $handler->display->display_options['fields']['keyword_id']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['keyword_id']['field'] = 'keyword_id';
  /* Field: Text campaign keywords: Keyword */
  $handler->display->display_options['fields']['keyword']['id'] = 'keyword';
  $handler->display->display_options['fields']['keyword']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['keyword']['field'] = 'keyword';
  /* Field: Text campaign keywords: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Text campaign keywords: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  /* Field: Text campaign keywords: Node id */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'ilao_sms_keyword';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['separator'] = '';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'campaign-keywords';
  $export['campaign_keywords'] = $view;

  $view = new view();
  $view->name = 'sms';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ilao_sms_message';
  $view->human_name = 'SMS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'SMS';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: SMS messages: ID */
  $handler->display->display_options['fields']['message_id']['id'] = 'message_id';
  $handler->display->display_options['fields']['message_id']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['message_id']['field'] = 'message_id';
  /* Field: SMS messages: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: SMS messages: From telephone number */
  $handler->display->display_options['fields']['from_number']['id'] = 'from_number';
  $handler->display->display_options['fields']['from_number']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['from_number']['field'] = 'from_number';
  /* Field: SMS messages: To telephone number */
  $handler->display->display_options['fields']['to_number']['id'] = 'to_number';
  $handler->display->display_options['fields']['to_number']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['to_number']['field'] = 'to_number';
  /* Field: SMS messages: Keyword */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  /* Field: SMS messages: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  /* Field: SMS messages: Text message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  /* Field: SMS messages: Text message type */
  $handler->display->display_options['fields']['message_type']['id'] = 'message_type';
  $handler->display->display_options['fields']['message_type']['table'] = 'ilao_sms_message';
  $handler->display->display_options['fields']['message_type']['field'] = 'message_type';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'sms';
  $export['sms'] = $view;

  return $export;
}
