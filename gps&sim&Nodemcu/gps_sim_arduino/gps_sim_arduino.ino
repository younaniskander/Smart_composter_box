#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Sender phone number with country code.
// Not the GSM module phone number
const String PHONE = "01024044831";

// GSM Module RX pin to Arduino pin 4
// GSM Module TX pin to Arduino pin 2
#define rxPin 4
#define txPin 2
SoftwareSerial sim800(rxPin, txPin); // Use Software Serial for SIM800L

SoftwareSerial neogps(10, 11); // Use Software Serial for NEO-6M GPS

TinyGPSPlus gps;

String smsStatus, senderNumber, receivedDate, msg;
boolean isReply = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Arduino serial initialized");
  
  sim800.begin(9600);
  Serial.println("SIM800L serial initialized");

  neogps.begin(9600);
  Serial.println("NEO-6M GPS serial initialized");

  smsStatus = "";
  senderNumber = "";
  receivedDate = "";
  msg = "";

  sim800.println("AT+CMGF=1"); // SMS text mode
  delay(1000);
  sim800.println("AT+CMGD=1,4"); // Delete all saved SMS
  delay(1000);
}

void loop() {
  //*************************************************
  while(sim800.available()){
    parseData(sim800.readString());
  }
//*************************************************
  while(Serial.available())  {
    sim800.println(Serial.readString());
  }
//*************************************************
} //main loop ends

// The rest of your functions remain unchanged.
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void parseData(String buff){
  Serial.println(buff);

  unsigned int len, index;
  //////////////////////////////////////////////////
  //Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index+2);
  buff.trim();
  //////////////////////////////////////////////////
  
  //////////////////////////////////////////////////
  if(buff != "OK"){
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();
    
    buff.remove(0, index+2);
    //Serial.println(buff);
    
    if(cmd == "+CMTI"){
      //get newly arrived memory location and store it in temp
      //temp = 4
      index = buff.indexOf(",");
      String temp = buff.substring(index+1, buff.length()); 
      temp = "AT+CMGR=" + temp + "\r"; 
      //AT+CMGR=4 i.e. get message stored at memory location 4
      sim800.println(temp); 
    }
    else if(cmd == "+CMGR"){
      extractSms(buff);
      Serial.println("Sender Number: "+senderNumber);
      Serial.println("PHONE: "+PHONE);
      if(senderNumber == PHONE){
        if(msg == "get location"){
          sendLocation();
        }
        else if(msg == "get speed"){
          Serial.println("PHONE: ");
        }
      }
      sim800.println("AT+CMGD=1,4"); //delete all saved SMS
      delay(1000);
      smsStatus = "";
      senderNumber="";
      receivedDate="";
      msg="";
    }
  //////////////////////////////////////////////////
  }
  else{
  //The result of AT Command is "OK"
  }
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void extractSms(String buff){
   unsigned int index;
   Serial.println(buff);

    index =buff.indexOf(",");
    smsStatus = buff.substring(1, index-1); 
    buff.remove(0, index+2);
    
    senderNumber = buff.substring(0, 13);
    buff.remove(0,19);
   
    receivedDate = buff.substring(0, 20);
    buff.remove(0,buff.indexOf("\r"));
    buff.trim();
    
    index =buff.indexOf("\n\r");
    buff = buff.substring(0, index);
    buff.trim();
    msg = buff;
    buff = "";
    msg.toLowerCase();

    //Serial.println("----------------------------------");
    //Serial.println(smsStatus);
    //Serial.println(senderNumber);
    //Serial.println(receivedDate);
    //Serial.println(msg);
    //Serial.println("----------------------------------");
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void sendLocation()
{
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }
  if (newData)      //If newData is true
  {
    Serial.print("Latitude= "); 
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude= "); 
    Serial.println(gps.location.lng(), 6);
    newData = false;
    delay(300);
    ///*
    sim800.print("AT+CMGF=1\r");
    delay(1000);
    sim800.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    sim800.print("http://maps.google.com/maps?q=loc:");
    sim800.print(gps.location.lat(), 6);
    sim800.print(",");
    sim800.print(gps.location.lng(), 6);
    delay(100);
    sim800.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(1000);
    Serial.println("GPS Location SMS Sent Successfully.");
    //*/
  }
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
