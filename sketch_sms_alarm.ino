/*

 Alarm notification
 
 created 04/04/2013
 by Hacklix
 
 */

// Include the GSM library
#include <GSM.h>

#define PINNUMBER ""

#define SMSNUMBER1 "0123456789"
#define SMSNUMBER2 ""
#define SMSNUMBER3 ""
#define SMSNUMBER4 ""

//en: msg booted
#define SMSSTART "Antifurto: Avviato"
//en: msg electric current blackout 
#define SMSBLACKOUT "Antifurto: Attenzione corrente mancante"
//en: msg electric current blackout off
#define SMSBLACKOUTOFF "Antifurto: Corrente tornata"
//en: msg intrusion attempt or triggered alarm
#define SMSINTRUSION "Antifurto: Attenzione tentativo di furto"

GSM gsmAccess;
GSM_SMS sms;
boolean sendhttp = false;

const int blackoutPin = 5;
const int intrusionPin = 6;

int blackout = 0;
int intrusion = 0;

void setup()
{

  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("SMS Messages Sender");

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
