The ilao_sms_surveys module provides support for sending webforms out of SMS.

It defines an entity for storing survey data and the associated webform submission.  Note that only completed
webforms are saved.  If a user quits during a survey, their information is not maintained.

In response to a survey being sent out to a user:
* the module captures the user's response
* sends the next question
* when all questions have been sent and answered, saves the webform submission
* webform conditionals are supported

One can use the survey entity and webform submission table to generate reports.  No reports for this have been provided.

Note: this relies on the Elysia cron module to send ILAO's OAS survey as an example.  Developers may build out their own
surveys in webform, schedule them in cron but this module needs to be aware of the specific survey.