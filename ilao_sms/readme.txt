ilao_sms is a package created to interact with Twilio to handle legal aid specific contexts.

It creates a custom entity that can be used to store SMS messages.  Please see the schema in the
 .install file for the available properties.
These properties are also available to Views to build out any reporting you may need.

Certain aspects of sharing legal information pertain specifically to ILAO's legal content structure and will require
changes to the code to re-use elsewhere.  For example, we disallow sharing of legal content in full text when it is
video content.

Certain text strings in the code will also need to be updated to match your website's messaging.
