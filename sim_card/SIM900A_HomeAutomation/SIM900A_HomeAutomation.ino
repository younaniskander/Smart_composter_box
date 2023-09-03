// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// GSM SIM900A Home Automation with Arduino

const int DEVICE1 = 2;
const int DEVICE2 = 3;
const int DEVICE3 = 4;
const int DEVICE4 = 5;
const int DEVICE5 = 6;
const int DEVICE6 = 7;
const int DEVICE7 = 8;
const int DEVICE8 = 9;
const int DEVICE9 = 10;
const int DEVICE10 = 11;

String textMessage;
String DEVICE1State = "LOW";
String DEVICE2State = "LOW";
String DEVICE3State = "LOW";
String DEVICE4State = "LOW";
String DEVICE5State = "LOW";
String DEVICE6State = "LOW";
String DEVICE7State = "LOW";
String DEVICE8State = "LOW";
String DEVICE9State = "LOW";
String DEVICE10State = "LOW";

void setup() 
{
 
  pinMode(DEVICE1, OUTPUT);
  pinMode(DEVICE2, OUTPUT);
  pinMode(DEVICE3, OUTPUT);
  pinMode(DEVICE4, OUTPUT);
  pinMode(DEVICE5, OUTPUT);
  pinMode(DEVICE6, OUTPUT);
  pinMode(DEVICE7, OUTPUT);
  pinMode(DEVICE8, OUTPUT);
  pinMode(DEVICE9, OUTPUT);
  pinMode(DEVICE10, OUTPUT);

  digitalWrite(DEVICE1, LOW);
  digitalWrite(DEVICE2, LOW);
  digitalWrite(DEVICE3, LOW);
  digitalWrite(DEVICE4, LOW);
  digitalWrite(DEVICE5, LOW);
  digitalWrite(DEVICE6, LOW);
  digitalWrite(DEVICE7, LOW);
  digitalWrite(DEVICE8, LOW);
  digitalWrite(DEVICE9, LOW);
  digitalWrite(DEVICE10, LOW);
  
  
  Serial.begin(19200);   // Initializing serial commmunication
  delay(20000);

 
  Serial.print("AT+CMGF=1\r");  // AT command to set SIM900 to SMS mode
  delay(100);

  Serial.print("AT+CNMI=2,2,0,0,0\r");  
  delay(100);
}

void loop() 
{
  if(Serial.available()>0){
    textMessage = Serial.readString(); 
    textMessage.toUpperCase();   
    delay(10);
  } 
  if(textMessage.indexOf("DEVICE1ON")>=0){
    digitalWrite(DEVICE1, HIGH);
    DEVICE1State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE1OFF")>=0){
    digitalWrite(DEVICE1, LOW);
    DEVICE1State = "off"; 
    textMessage = ""; 
  }
   if(textMessage.indexOf("DEVICE2ON")>=0){
    digitalWrite(DEVICE2, HIGH);
    DEVICE2State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE2OFF")>=0){
    digitalWrite(DEVICE2, LOW);
    DEVICE2State = "off"; 
    textMessage = ""; 
  }
   if(textMessage.indexOf("DEVICE3ON")>=0){
    digitalWrite(DEVICE3, HIGH);
    DEVICE3State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE3OFF")>=0){
    digitalWrite(DEVICE3, LOW);
    DEVICE3State = "off"; 
    textMessage = ""; 
  }
   if(textMessage.indexOf("DEVICE4ON")>=0){
    digitalWrite(DEVICE4, HIGH);
    DEVICE4State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE4OFF")>=0){
    digitalWrite(DEVICE4, LOW);
    DEVICE4State = "off"; 
    textMessage = ""; 
  }
  
   if(textMessage.indexOf("DEVICE5ON")>=0){
    digitalWrite(DEVICE5, HIGH);
    DEVICE5State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE5OFF")>=0){
    digitalWrite(DEVICE5, LOW);
    DEVICE5State = "off"; 
    textMessage = ""; 
  }
  
   if(textMessage.indexOf("DEVICE6ON")>=0){
    digitalWrite(DEVICE6, HIGH);
    DEVICE6State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE6OFF")>=0){
    digitalWrite(DEVICE6, LOW);
   DEVICE6State = "off"; 
    textMessage = ""; 
  }
  
   if(textMessage.indexOf("DEVICE7ON")>=0){
    digitalWrite(DEVICE7, HIGH);
    DEVICE7State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("DEVICE7OFF")>=0){
    digitalWrite(DEVICE7, LOW);
    DEVICE7State = "off"; 
    textMessage = ""; 
  }
  
   if(textMessage.indexOf("DEVICE8ON")>=0){
    digitalWrite(DEVICE8, HIGH);
    DEVICE8State = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("LDEVICE8OFF")>=0){
    digitalWrite(DEVICE8, LOW);
    DEVICE8State = "off"; 
    textMessage = ""; 
  }
  if(textMessage.indexOf("DEVICE9OFF")>=0){
    digitalWrite(DEVICE9, LOW);
    DEVICE9State = "off"; 
    textMessage = ""; 
  }
  if(textMessage.indexOf("DEVICE9ON")>=0){
    digitalWrite(DEVICE9, HIGH);
    DEVICE9State = "on"; 
    textMessage = ""; 
  }
  if(textMessage.indexOf("DEVICE10OFF")>=0){
    digitalWrite(DEVICE10, LOW);
    DEVICE10State = "off"; 
    textMessage = ""; 
  }
  if(textMessage.indexOf("DEVICE10ON")>=0){
    digitalWrite(DEVICE10, HIGH);
    DEVICE10State = "on"; 
    textMessage = ""; 
  }
  if(textMessage.indexOf("ALLDEVICEOFF")>=0){
    digitalWrite(DEVICE1, LOW);
    digitalWrite(DEVICE2, LOW);
    digitalWrite(DEVICE3, LOW);
    digitalWrite(DEVICE4, LOW);
    digitalWrite(DEVICE5, LOW);
    digitalWrite(DEVICE6, LOW);
    digitalWrite(DEVICE7, LOW);
    digitalWrite(DEVICE8, LOW);
    digitalWrite(DEVICE9, LOW);
    digitalWrite(DEVICE10, LOW);
    DEVICE1State = "off"; 
    DEVICE2State = "off";
    DEVICE3State = "off";
    DEVICE4State = "off";
    DEVICE5State = "off";
    DEVICE6State = "off";
    DEVICE7State = "off";
    DEVICE8State = "off";
    DEVICE9State = "off";
    DEVICE10State = "off";
    textMessage = ""; 
  }
  if(textMessage.indexOf("ALLDEVICEON")>=0){
    digitalWrite(DEVICE1, HIGH);
    digitalWrite(DEVICE2, HIGH);
    digitalWrite(DEVICE3, HIGH);
    digitalWrite(DEVICE4, HIGH);
    digitalWrite(DEVICE5, HIGH);
    digitalWrite(DEVICE6, HIGH);
    digitalWrite(DEVICE7, HIGH);
    digitalWrite(DEVICE8, HIGH);
    digitalWrite(DEVICE9, HIGH);
    digitalWrite(DEVICE10, HIGH);
    DEVICE1State = "on"; 
    DEVICE2State = "on";
    DEVICE3State = "on";
    DEVICE4State = "on";
    DEVICE5State = "on";
    DEVICE6State = "on";
    DEVICE7State = "on";
    DEVICE8State = "on";
    DEVICE9State = "on";
    DEVICE10State = "on";
    textMessage = ""; 
  }
 
  if(textMessage.indexOf("DEVICE1STATE")>=0){
    String message = "DEVICE1 is " + DEVICE1State;
    sendSMS(message);
    textMessage = "";
  }
  if(textMessage.indexOf("DEVICE2STATE")>=0){
    String message = "DEVICE2 is " + DEVICE2State;
    sendSMS(message);
    textMessage = "";
  }
  if(textMessage.indexOf("DEVICE3STATE")>=0){
    String message = "DEVICE3 is " + DEVICE3State;
    sendSMS(message);
    textMessage = "";
  }
    if(textMessage.indexOf("DEVICE4STATE")>=0){
    String message = "DEVICE4 is " + DEVICE4State;
    sendSMS(message);
    textMessage = "";
  }
    if(textMessage.indexOf("DEVICE5STATE")>=0){
    String message = "DEVICE5 is " + DEVICE5State;
    sendSMS(message);
    textMessage = "";
  }
    if(textMessage.indexOf("DEVICE6STATE")>=0){
    String message = "DEVICE6 is " + DEVICE6State;
    sendSMS(message);
    textMessage = "";
  }
    if(textMessage.indexOf("DEVICE7STATE")>=0){
    String message = "DEVICE7 is " + DEVICE7State;
    sendSMS(message);
    textMessage = "";
  }
    if(textMessage.indexOf("DEVICE8STATE")>=0){
    String message = "DEVICE8 is " + DEVICE8State;
    sendSMS(message);
    textMessage = "";
  }
  if(textMessage.indexOf("DEVICE9STATE")>=0){
    String message = "DEVICE9 is " + DEVICE9State;
    sendSMS(message);
    textMessage = "";
  }
  if(textMessage.indexOf("DEVICE10STATE")>=0){
    String message = "DEVICE10 is " + DEVICE10State;
    sendSMS(message);
    textMessage = "";
  }
}  

void sendSMS(String message)   // Function to sends SMS
{
  // AT command to set SIM900 into SMS mode
  Serial.print("AT+CMGF=1\r"); 
  delay(100);
  Serial.println("AT + CMGS = \"+91XXXXXXXXXX\"");   //Country code and Mobile Number +91XXXXXXXXXX
  delay(100);
  Serial.println(message); 
  delay(100);
  Serial.println((char)26); 
  delay(100);
  Serial.println();
  delay(5000);  
}
