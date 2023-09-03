#include "Arduino.h"
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

SoftwareSerial mySerial(10, 11); // RX, TX for IOT-GA6-B

#define BLYNK_PRINT Serial
#define TINY_GSM_MODEM_SIM800

#include "Adafruit_FONA.h"

// Adafruit_FONA setup for IOT-GA6-B
#define FONA_RST 9
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char apn[] = "YOUR_APN";
char user[] = "";
char pass[] = "";

TinyGsm modem(fona);
BlynkTimer timer;

int state_relay1 = 0;
int state_relay2 = 0;
int state_relay3 = 0;
int state_relay4 = 0;

#define virtual_pin1 V1
#define virtual_pin2 V2
#define virtual_pin3 V3
#define virtual_pin4 V4

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  delay(10);
  mySerial.println("AT");

  pinMode(12, OUTPUT); // Relays connected to D5, D6, D7, D8
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);

  fonaSerial->begin(9600);
  if (!fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
  fona.println("AT+CMGF=1");
  delay(1000);
  fona.print("AT+CSMP=17,167,0,0\r");
  delay(1000);
  fona.print("AT+CNMI=2,1\r\n");

  Blynk.begin(auth, modem, apn, user, pass);
  Blynk.virtualWrite(virtual_pin1, state_relay1);
  Blynk.virtualWrite(virtual_pin2, state_relay2);
  Blynk.virtualWrite(virtual_pin3, state_relay3);
  Blynk.virtualWrite(virtual_pin4, state_relay4);

  timer.setInterval(1L, handle_sms);
}

void loop() {
  Blynk.run();
  timer.run();
}

void handle_sms() {
  while (mySerial.available()) {
    fona.print((char)mySerial.read());
  }

  String gsm_buff = "";
  int slot = 0;
  uint16_t smslen;
  gsm_buff = fona.readString();
  int len = gsm_buff.length();

  if (len > 10) {
    gsm_buff = gsm_buff.substring(14, len);
    slot = gsm_buff.toInt();
    if (slot == 0) {
      return;
    }

    char sms_buffer[255];
    if (!fona.readSMS(slot, sms_buffer, 250, &smslen)) {
      Serial.println(F("Failed!"));
      return;
    }

    char caller_id[32];
    if (!fona.getSMSSender(slot, caller_id, 31)) {
      Serial.println("Didn't find SMS message in slot!");
      return;
    }

    if (String(PHONE) != String(caller_id)) {
      Serial.println("The phone number is not Registered.");
      Serial.println("Please use the Registered Phone Number.");
    }
    else {
      String sms_temp = sms_buffer;
      sms_temp.toLowerCase();
      Serial.println("SMS: " + sms_temp);
      Serial.println("From: " + caller_id);

      if (sms_temp == "1on") {
        state_relay1 = 1;
        digitalWrite(12, HIGH);
        Blynk.virtualWrite(virtual_pin1, state_relay1);
        fona.sendSMS(caller_id, "Relay 1 is ON");
        Serial.println("Response: Relay 1 is ON");
      }
      else if (sms_temp == "1off") {
        state_relay1 = 0;
        digitalWrite(12, LOW);
        Blynk.virtualWrite(virtual_pin1, state_relay1);
        fona.sendSMS(caller_id, "Relay 1 is OFF");
        Serial.println("Response: Relay 1 is OFF");
      }
      if(sms_temp == "2on"){
        state_relay2 =1;
        digitalWrite(pin_relay2, HIGH);
        Blynk.virtualWrite(virtual_pin2, state_relay2);
        fona.sendSMS(caller_id, "Relay 2 is ON");
        Serial.println("Response: Relay 2 is ON");
      }
      //_________________________________________
      if(sms_temp == "2off"){
        state_relay2 =0;
        digitalWrite(pin_relay2, LOW);
        Blynk.virtualWrite(virtual_pin2, state_relay2);
        fona.sendSMS(caller_id, "Relay 2 is OFF");
        Serial.println("Response: Relay 2 is OFF");
      }
      //_________________________________________ 
      if(sms_temp == "3on"){
        state_relay3 =1;
        digitalWrite(pin_relay3, HIGH);
        fona.sendSMS(caller_id, "Relay 3 is ON");
        Blynk.virtualWrite(virtual_pin3, state_relay3);
        Serial.println("Response: Relay 3 is ON");
      }
      //_________________________________________
      if(sms_temp == "3off"){
        state_relay3 =0;
        digitalWrite(pin_relay3, LOW);
        fona.sendSMS(caller_id, "Relay 3 is OFF");
        Blynk.virtualWrite(virtual_pin3, state_relay3);
        Serial.println("Response: Relay 3 is OFF");
      }
      //_________________________________________
      if(sms_temp == "4on"){
        state_relay4 =1;
        digitalWrite(pin_relay4, HIGH);
        Blynk.virtualWrite(virtual_pin4, state_relay4);
        fona.sendSMS(caller_id, "Relay 4 is ON");
        Serial.println("Response: Relay 4 is ON");
      }
      //_________________________________________
      if(sms_temp == "4off"){
        state_relay4 =0;
        digitalWrite(pin_relay4, LOW);
        Blynk.virtualWrite(virtual_pin4, state_relay4);
        fona.sendSMS(caller_id, "Relay 4 is OFF");
        Serial.println("Response: Relay 4 is OFF");
      }
      else {
        fona.sendSMS(caller_id, "ERROR: Send SMS with valid command");
      }
    }

    fona.deleteSMS(slot);
    fona.print(F("AT+CMGD=1,4\r"));
  }
}
