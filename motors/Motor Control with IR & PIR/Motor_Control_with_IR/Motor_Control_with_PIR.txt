// Define the pins for the L298N motor driver
const int motorAEnablePin = 3;
const int motorAInput1Pin = 4;
const int motorAInput2Pin = 5;

const int motorBEnablePin = 6;
const int motorBInput1Pin = 7;
const int motorBInput2Pin = 8;

// Define the PIR motion sensor pin
const int pirSensorPin = 2;

void setup() {
  // Set motor control pins as OUTPUT
  pinMode(motorAEnablePin, OUTPUT);
  pinMode(motorAInput1Pin, OUTPUT);
  pinMode(motorAInput2Pin, OUTPUT);

  pinMode(motorBEnablePin, OUTPUT);
  pinMode(motorBInput1Pin, OUTPUT);
  pinMode(motorBInput2Pin, OUTPUT);

  // Set PIR motion sensor pin as INPUT
  pinMode(pirSensorPin, INPUT);

  // Initialize motor speeds and stop the motors
  analogWrite(motorAEnablePin, 0);
  analogWrite(motorBEnablePin, 0);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the PIR motion sensor
  int pirValue = digitalRead(pirSensorPin);

  if (pirValue == HIGH) {
    Serial.println("Motion detected!");

    // Run motors forward
    digitalWrite(motorAInput1Pin, HIGH);
    digitalWrite(motorAInput2Pin, LOW);
    analogWrite(motorAEnablePin, 255);

    digitalWrite(motorBInput1Pin, HIGH);
    digitalWrite(motorBInput2Pin, LOW);
    analogWrite(motorBEnablePin, 255);

    // Run motors for 30 seconds
    delay(30000);

    // Stop motors
    analogWrite(motorAEnablePin, 0);
    analogWrite(motorBEnablePin, 0);
  }
}