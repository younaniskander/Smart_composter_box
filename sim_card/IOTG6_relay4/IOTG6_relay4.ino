#include <SoftwareSerial.h>

#define GSM_RX 2
#define GSM_TX 3
SoftwareSerial sim(GSM_RX, GSM_TX);

String number = "+201111916960";

const int relay1Pin = 4;  // Define the pins for your 4 relays
const int relay2Pin = 5;
const int relay3Pin = 6;
const int relay4Pin = 7;

void setup() {
  Serial.begin(115200);
  sim.begin(115200);
  pinMode(relay1Pin, OUTPUT);  // Set relay pins as outputs
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);

    // Set all relay pins to LOW (off) state initially
 // digitalWrite(relay1Pin, LOW);
//digitalWrite(relay2Pin, LOW);
////  digitalWrite(relay3Pin, LOW);
///  digitalWrite(relay4Pin, LOW);


  Serial.println("System Started...");
  delay(1000);

  Serial.println("Communicating GSM/GPS.....");
  call();
  delay(8000);
  sms();
}

void loop() {
  // Your loop code goes here
}

void sms() {
  Serial.println("Sending Message");
  sim.println("AT+CMGF=1");
  delay(1000);
  Serial.println("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "Sample SMS is sending";
  sim.println(SMS);

  delay(100);
  sim.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
}

void call() {
  sim.print(F("ATD"));
  sim.print(number);
  sim.print(F(";\r\n"));
}

// Function to control the relays based on received SMS
void controlRelays(String command) {
  if (command == "relay1on") {
    digitalWrite(relay1Pin, HIGH);
  } else if (command == "relay1off") {
    digitalWrite(relay1Pin, LOW);
  } else if (command == "relay2on") {
    digitalWrite(relay2Pin, HIGH);
  } else if (command == "relay2off") {
    digitalWrite(relay2Pin, LOW);
  } else if (command == "relay3on") {
    digitalWrite(relay3Pin, HIGH);
  } else if (command == "relay3off") {
    digitalWrite(relay3Pin, LOW);
  } else if (command == "relay4on") {
    digitalWrite(relay4Pin, HIGH);
  } else if (command == "relay4off") {
    digitalWrite(relay4Pin, LOW);
  }
}

void parseReceivedSMS(String sms) {
  sms.toLowerCase();
  sms.trim();

  if (sms == "relay1on" || sms == "relay1off" ||
      sms == "relay2on" || sms == "relay2off" ||
      sms == "relay3on" || sms == "relay3off" ||
      sms == "relay4on" || sms == "relay4off") {
    controlRelays(sms);
  }
}

// Handle incoming data from SIM module
void handleSIMData() {
  while (sim.available()) {
    char c = sim.read();
    Serial.print(c);
    if (c == '\n') {
      sim.readString(); // Clear the buffer
    }
  }
}
