The ILAO SMS repository includes the following 3 modules:
* ilao_sms
* ilao_sms_campaigns
* ilao_sms_surveys


Additionally, the following dependencies exist:
* Webform
* Twilio

To create any reports you might need, we recommend installing Views.

Full documentation is available here:  https://docs.google.com/document/d/18RmpaRKHPY3DTC700ZQix1HJHuqtuxlj-5_cqd_QNYM/edit


To interact:  the ilao_sms_twilio_sms_incoming function controls all of the logic ILAO created for all incoming requests.  It determines if an incoming request is a campaign keyword, survey response, or something else and handles accordingly.
