/*

 arduino-dialer-gsm
 
 created 04/04/2013
 by Hacklix
 
 */

// Include the GSM library
#include <GSM.h>

#define PINNUMBER ""

#define SMSNUMBER1 "078332328929"
#define SMSNUMBER2 ""
#define SMSNUMBER3 ""
#define SMSNUMBER4 ""

//en: initial boot message
#define SMSSTART "LH Test Message"
//en: low pressure message 
#define SMS_LOW_PRESSURE "WARNING: Low Pressure"
//en: high pressure message
#define SMS_HIGH_PRESSURE "WARNING:High Pressure"
//en: power failure message
#define SMS_POWER_FAILURE "POWER FAILURE"

GSM gsmAccess;
GSM_SMS sms;
boolean sendhttp = false;

const int low_pressure = 5;
const int high_pressure = 6;

int lowpressure = 0;
int highpressure = 0;

void setup()
{

  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("SMS Messages Sender...");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  
  pinMode(blackoutPin, INPUT);
  pinMode(intrusionPin, INPUT);
  
  sendSms(SMSNUMBER1,SMSSTART);
}



void loop()
{
  
  //TODO: READ SMS

  //BLACKOUT 
  if(blackout != digitalRead(blackoutPin))
  {
     
     Serial.println("\nblackout chenged\n"); //DEBUG

     blackout = digitalRead(blackoutPin);
     
     if(blackout == 1){
        sendSms(SMSNUMBER1,SMSBLACKOUT);
        //sendSms(SMSNUMBER2,SMSBLACKOUT);
        //sendSms(SMSNUMBER3,SMSBLACKOUT);
        //sendSms(SMSNUMBER4,SMSBLACKOUT);
        sendHttp(SMSBLACKOUT);
     }else{
        sendSms(SMSNUMBER1,SMSBLACKOUTOFF);      
        sendHttp(SMSBLACKOUTOFF);
     } 
  }
  
  Serial.print("\nblackout:"); //DEBUG
  Serial.println(blackout, DEC); //DEBUG
  
  //INTRUSION
  if(intrusion != digitalRead(intrusionPin))
  {

     Serial.println("\nintrusion chenged\n"); //DEBUG

     intrusion = digitalRead(intrusionPin);
     
     if(intrusion == 1){
        sendSms(SMSNUMBER1,SMSINTRUSION);
        //sendSms(SMSNUMBER2,SMSINTRUSION);
        //sendSms(SMSNUMBER3,SMSINTRUSION);
        //sendSms(SMSNUMBER4,SMSINTRUSION);  
        sendHttp(SMSINTRUSION);      
     }
     
  }  
  
  Serial.print("\nintrusion:"); //DEBUG
  Serial.println(intrusion, DEC); //DEBUG
  
  delay(1000);

}


void sendSms(char* to, char* msg)
{
    sms.beginSMS(to);
    sms.print(msg);
    sms.endSMS(); 
    Serial.println("\nSMS SEND COMPLETE!\n");
}

void sendHttp(char* msg)
{
    //TODO
}
