This module defines two entities:
* ilao_sms_campaign which defines a campaign
* ilao_sms_keyword which defines a campaign keyword associated with a campaign

When an incoming sms is received and the text matches a keyword, the response (either message or text of content)
will be sent to the user.  A record of the incoming and outgoing messages are kept as entities in the ilao_sms_message
 table