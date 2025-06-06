#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <ESP_Google_Sheet_Client.h>
#include <time.h>

// wifi credentials
#define WIFI_SSID     "your_wifi_ssid"
#define WIFI_PASS     "your_wifi_password"

//Sinric Pro Credentials
#define APP_KEY       "your_app_key"
#define APP_SECRET    "your_app_secret"

#define BULB_DEVICE_ID "your_bulb_device_id"
#define LED_DEVICE_ID  "your_led_device_id"

#define RELAY_PIN_BULB 23
#define RELAY_PIN_LED  25
#define TOUCH_PIN_BULB 14
#define TOUCH_PIN_LED  27
#define TOUCH_THRESHOLD 60

// Google Sheets Credentials 
#define PROJECT_ID      "your_project_id"
#define CLIENT_EMAIL    "your_service_account_email"
const char PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN PRIVATE KEY-----
your_private_key_here
-----END PRIVATE KEY-----
)EOF";
const char SPREADSHEET_ID[] = "your_spreadsheet_id";

// Time Server Settings
const char* ntpServer = "in.pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

// Globals 
SparkFun_APDS9960 apds = SparkFun_APDS9960();
bool bulbState = false;
bool ledState = false;
unsigned long lastTouchBulb = 0;
unsigned long lastTouchLED = 0;
const unsigned long debounceDelay = 300;

// Function Prototypes 
void setupWiFi();
void setupRelaysAndTouch();
void setupGestureSensor();
void checkTouchInputs();
void handleGesture();
void toggleBulb();
void toggleLED();
void setupSinric();
bool onPowerState(const String &deviceId, bool &state);
void setupTime();

// Setup
void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupRelaysAndTouch();
  setupGestureSensor();
  setupSinric();
  setupTime();
}

void loop() {
  checkTouchInputs();
  handleGesture();
  SinricPro.handle();
}

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");
}

void setupRelaysAndTouch() {
  pinMode(RELAY_PIN_BULB, OUTPUT);
  pinMode(RELAY_PIN_LED, OUTPUT);
  digitalWrite(RELAY_PIN_BULB, LOW);
  digitalWrite(RELAY_PIN_LED, LOW);
}

void checkTouchInputs() {
  if (touchRead(TOUCH_PIN_BULB) < TOUCH_THRESHOLD && millis() - lastTouchBulb > debounceDelay) {
    toggleBulb();
    lastTouchBulb = millis();
  }
  if (touchRead(TOUCH_PIN_LED) < TOUCH_THRESHOLD && millis() - lastTouchLED > debounceDelay) {
    toggleLED();
    lastTouchLED = millis();
  }
}

void toggleBulb() {
  bulbState = !bulbState;
  digitalWrite(RELAY_PIN_BULB, bulbState ? HIGH : LOW);
  Serial.println(bulbState ? "Bulb ON" : "Bulb OFF");
}

void toggleLED() {
  ledState = !ledState;
  digitalWrite(RELAY_PIN_LED, ledState ? HIGH : LOW);
  Serial.println(ledState ? "LED ON" : "LED OFF");
}

// Gesture Sensor 
void setupGestureSensor() {
  if (apds.init()) {
    Serial.println("APDS9960 initialization complete");
  } else {
    Serial.println("APDS9960 initialization failed");
    return;
  }

  if (apds.enableGestureSensor(true)) {
    Serial.println("Gesture sensor enabled");
  } else {
    Serial.println("Failed to enable gesture sensor");
  }
}

void handleGesture() {
  if (apds.isGestureAvailable()) {
    int gesture = apds.readGesture();
    switch (gesture) {
      case DIR_UP:
      case DIR_DOWN:
        toggleLED();
        break;
      case DIR_LEFT:
      case DIR_RIGHT:
        toggleBulb();
        break;
      default:
        Serial.println("Unknown Gesture");
        break;
    }
  }
}

// Sinric 
void setupSinric() {
  SinricProSwitch& myBulb = SinricPro[BULB_DEVICE_ID];
  SinricProSwitch& myLED  = SinricPro[LED_DEVICE_ID];

  myBulb.onPowerState(onPowerState);
  myLED.onPowerState(onPowerState);

  SinricPro.onConnected([]() { Serial.println("Connected to SinricPro"); });
  SinricPro.onDisconnected([]() { Serial.println("Disconnected from SinricPro"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

bool onPowerState(const String &deviceId, bool &state) {
  if (deviceId == BULB_DEVICE_ID) {
    bulbState = state;
    digitalWrite(RELAY_PIN_BULB, bulbState ? HIGH : LOW);
  } else if (deviceId == LED_DEVICE_ID) {
    ledState = state;
    digitalWrite(RELAY_PIN_LED, ledState ? HIGH : LOW);
  }
  return true;
}

void setupTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
