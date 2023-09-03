#include <SIM800L-RAW.h>
#include <SIM800L.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <FirebaseESP8266.h>

// Firebase Configuration
#define FIREBASE_HOST "https://gps1-47470-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jhw41Z5OJIMZ5pk1iGO6mLn6zbxLmWVN7RS1DCgJ"

// Wi-Fi Configuration
const char *WIFI_SSID = "ENTER_WIFI_SSID";
const char *WIFI_PASSWORD = "ENTER_WIFI_PASSWORD";

// GPS Configuration
const int RXPin = 4, TXPin = 5;
SoftwareSerial neo6m(RXPin, TXPin);
TinyGPSPlus gps;

// Google Sheets Configuration
const char *ssid = "ENTER_YOUR_WIFI_SSID";
const char *password = "ENTER_YOUR_WIFI_PASSWORD";
String GOOGLE_SCRIPT_ID = "AKfycbwZOTuzmhNYBKvzReLDha-GrcCKqGquwbVCUlTVuhH3P4dHnQjOCqOljwCdKC-kjFIPuQ";

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Initialize GPS
  neo6m.begin(9600);

  // Connect to Wi-Fi
  wifiConnect();

  // Initialize Firebase
  Serial.println("Connecting Firebase.....");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase OK.");
}

void loop() {
  smartdelay_gps(1000);

  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    if (Firebase.setFloat(firebaseData, "/GPS/f_latitude", latitude)) {
      print_ok();
    } else {
      print_fail();
    }

    if (Firebase.setFloat(firebaseData, "/GPS/f_longitude", longitude)) {
      print_ok();
    } else {
      print_fail();
    }

    print_speed();
  } else {
    Serial.println("No valid GPS data found.");
  }

  delay(5000);
}

static void smartdelay_gps(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (neo6m.available())
      gps.encode(neo6m.read());
  } while (millis() - start < ms);
}

void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void print_ok() {
  Serial.println("------------------------------------");
  Serial.println("OK");
  Serial.println("PATH: " + firebaseData.dataPath());
  Serial.println("TYPE: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.println("------------------------------------");
  Serial.println();
}

void print_fail() {
  Serial.println("------------------------------------");
  Serial.println("FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

void print_speed() {
  if (gps.location.isValid()) {
    String param;
    param = "latitude=" + String(gps.location.lat(), 6);
    param += "&longitude=" + String(gps.location.lng(), 6);
    param += "&speed=" + String(gps.speed.kmph());
    param += "&satellites=" + String(gps.satellites.value());
    param += "&altitude=" + String(gps.altitude.meters());
    param += "&gps_time=" + String(gps.time.value());
    param += "&gps_date=" + String(gps.date.value());

    Serial.println(param);
    write_to_google_sheet(param);
  } else {
    Serial.println("No valid GPS data for Google Sheets.");
  }
}

void write_to_google_sheet(String params) {
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + params;
  Serial.println("Posting GPS data to Google Sheet");

  // Start posting data to Google Sheets
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);

  // Get response from Google Sheets
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload: " + payload);
  }

  http.end();
}
