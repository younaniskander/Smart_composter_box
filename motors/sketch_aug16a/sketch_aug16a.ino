#define bt_F A1 // Clockwise Button
#define bt_S A2 // Stop Button
#define bt_B A3 // Anticlockwise Button

#define M1_Ena 5 // Enable1 L298 for PWM
#define M1_in1 7 // In1  L298 for Clockwise
#define M1_in2 8  // In2  L298 for Anticlockwise

#define M2_Ena 6  // Enable2 L298 for PWM
#define M2_in1 9  // In3  L298 for Clockwise
#define M2_in2 10  // In4  L298 for Anticlockwise

int set = 0;
int pirPin = 11; // PIR Sensor output pin

void setup() {
  Serial.begin(9600);
 
  pinMode(bt_F, INPUT_PULLUP);
  pinMode(bt_S, INPUT_PULLUP);
  pinMode(bt_B, INPUT_PULLUP);

  pinMode(M1_Ena, OUTPUT);
  pinMode(M1_in1, OUTPUT);
  pinMode(M1_in2, OUTPUT);

  pinMode(M2_Ena, OUTPUT);
  pinMode(M2_in1, OUTPUT);
  pinMode(M2_in2, OUTPUT);

  pinMode(pirPin, INPUT); // PIR Sensor
  

//   // Set default state of motors to "off"
//  digitalWrite(M1_in1, LOW);
//  digitalWrite(M1_in2, LOW);
//  analogWrite(M1_Ena, 255);
//
//  digitalWrite(M2_in1, LOW);
//  digitalWrite(M2_in2, LOW);
//  analogWrite(M2_Ena, 255);
}

void loop() {
  
  int pirValue = digitalRead(pirPin); // Read PIR sensor value

  if (pirValue == HIGH) {
    set = 0; // Stop motors if object detected by PIR sensor
  }
  else {
    if (digitalRead(bt_F) == 0) {
      set = 1;
    }
    if (digitalRead(bt_S) == 0) {
      set = 0;
    }
    if (digitalRead(bt_B) == 0) {
      set = 2;
    }
  }

  if (set == 0) {
    // stop
    digitalWrite(M1_in1, LOW);
    digitalWrite(M1_in2, LOW);
    analogWrite(M1_Ena, 255);
  
    digitalWrite(M2_in1, LOW);
    digitalWrite(M2_in2, LOW);
    analogWrite(M2_Ena, 255);
  }
  if (set == 1) {
    // clock
    digitalWrite(M1_in1, HIGH);
    digitalWrite(M1_in2, LOW);
    analogWrite(M1_Ena, 255);

    digitalWrite(M2_in1, HIGH);
    digitalWrite(M2_in2, LOW);
    analogWrite(M2_Ena, 255);
  }
  if (set == 2) {
    // anti-clock
    digitalWrite(M1_in1, LOW);
    digitalWrite(M1_in2, HIGH);
    analogWrite(M1_Ena, 255);

    digitalWrite(M2_in1, LOW);
    digitalWrite(M2_in2, HIGH);
    analogWrite(M2_Ena, 255);
  }

  delay(50);
}
