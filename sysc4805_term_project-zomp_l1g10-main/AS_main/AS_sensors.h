#include <Ultrasonic.h>

// Input Pin declarations for the line and the forward ultrasonic sensors
#define LINE_L_IN_PIN A1
#define LINE_R_IN_PIN A0
#define OBJ_FR_IN_PIN A8
#define OBJ_FL_IN_PIN A7

// Trigger and Echo Pin declarations for the left and the right ultrasonic sensors
#define OBJ_L_TRIG_PIN 12
#define OBJ_L_ECHO_PIN 13
#define OBJ_R_TRIG_PIN 10
#define OBJ_R_ECHO_PIN 11

// Predetermined thresholds for line perimeteur and object (Front, left and right) detections
#define OBJ_FLR_THRESHOLD 100
#define OBJ_F_THRESHOLD 160
#define LINE_L_THRESHOLD 900
#define LINE_R_THRESHOLD 900
#define OBJ_LR_THRESHOLD 100

bool printReadings = true;

// Configuring the left and right ultrasonic sensors.
Ultrasonic ultrasonicL(OBJ_L_TRIG_PIN, OBJ_L_ECHO_PIN, 15000UL);
Ultrasonic ultrasonicR(OBJ_R_TRIG_PIN, OBJ_R_ECHO_PIN, 15000UL);

// The function 'setupLineSensorPins' configures the pin declarations for the line sensors.
// Parameter: None.
// Returns: Void.
void setupLineSensorPins() {
  pinMode(LINE_L_IN_PIN, INPUT_PULLUP);
  pinMode(LINE_R_IN_PIN, INPUT_PULLUP);
}

// The function 'setupFrontSensorPins' configures the pin declarations for the forward ultrasonic sensor.
// Parameter: None.
// Returns: Void.
void setupFrontSensorPins() {
  pinMode(OBJ_FR_IN_PIN, INPUT_PULLUP);
  pinMode(OBJ_FL_IN_PIN, INPUT_PULLUP);
  pinMode(A10, INPUT_PULLUP);
}

// The function 'isObjFRDetectingObject' determines whether the front right sensor detects an object.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isObjFDetectingObject() {
  int reading = analogRead(A10);
  if(printReadings) Serial.println("[INFO] F: " + String(reading));
  return reading > OBJ_F_THRESHOLD;
}

// The function 'isObjFRDetectingObject' determines whether the front right sensor detects an object.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isObjFRDetectingObject() {
  int reading = analogRead(OBJ_FR_IN_PIN);
  if(printReadings) Serial.println("[INFO] FOR: " + String(reading));
  return reading < OBJ_FLR_THRESHOLD;
}

// The function 'isObjFLDetectingObject' determines whether the front left sensor detects an object.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isObjFLDetectingObject() {
  int reading = analogRead(OBJ_FL_IN_PIN);
  if(printReadings) Serial.println("[INFO] FOL: " + String(reading));
  return reading < OBJ_FLR_THRESHOLD;
}

// The function 'isObjLDetectingObject' determines whether the leftmost sensor detects an object.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isObjLDetectingObject() {
  int reading = ultrasonicL.read();
  if(printReadings) Serial.println("[INFO] LO: " + String(reading));
  return reading < OBJ_LR_THRESHOLD && reading > 3;
}

// The function 'isObjRDetectingObject' determines whether the rightmost sensor detects an object.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isObjRDetectingObject() {
  int reading = ultrasonicR.read();
  if(printReadings) Serial.println("[INFO] RO: " + String(reading));
  return reading < OBJ_LR_THRESHOLD && reading > 3;
}

// The function 'isLineLDetectingLine' determines whether the left line follower sensor detects the perimeter.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isLineLDetectingLine() {
  int reading = analogRead(LINE_L_IN_PIN);
  if(printReadings) Serial.println("[INFO] LL: " + String(reading));
  return reading > LINE_L_THRESHOLD;
}

// The function 'isLineRDetectingLine' determines whether the right line follower sensor detects the perimeter.
// This happens by comparing the detected value with the predetermined threshold.
// Parameter: None.
// Returns: Boolean.
bool isLineRDetectingLine() {
  int reading = analogRead(LINE_R_IN_PIN);
  if(printReadings) Serial.println("[INFO] RL: " + String(reading));
  return reading > LINE_R_THRESHOLD;
}
