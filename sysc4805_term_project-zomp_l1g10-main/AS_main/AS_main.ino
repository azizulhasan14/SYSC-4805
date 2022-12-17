#include "AS_sensors.h"

#define BACKWARD_MVMT_TIME_MS 800
#define ROTATION_MVMT_TIME_MS 2500.0

#define MOTOR_FREQUENCY 1000
#define MOTOR_DUTY 1.8

#define MOTOR_DUTY_MANEUVER 1.5

#define DEBOUNCING_READINGS 5

void setup() {
  //Setting up different configurations before system start. Pins for sensors and wheel encoders
  // are all done here. The WDT is also set up here.
  Serial.begin(9600);
  randomSeed(320);

  setupLEDPins();

  setupWheelDirectionPins();
  setupWheelSpeedPin(MOTOR_FREQUENCY, MOTOR_DUTY);

  setupLineSensorPins();
  setupFrontSensorPins();

  setupBuckRegulatorPin();

  setupWDT();
  startWheels();
  printf("[INFO]: SYSTEM START \n");
}

void loop()
{
  checkBuckRegulator();   //Checks whether we have enough power
  resetLEDs();

  // the following snippet of code constitutes the logic the snowplow will be adhering to when operational.

  // There are 7 different scenarios the snowplow will be in: detecting the line perimeter on the right,
  // detecting the line perimeter on the left, detecting an object on the left, detecting an object on the right,
  // detecting an object on the front and finally forward.

  // Each Scenario will set flags/LEDS (except for forward) and trigger an ISR and then run through that ISR.


  if (isLineRDetectingLine()) {
    setLEDs(1, 0, 0);
    blockingBackward(BACKWARD_MVMT_TIME_MS);
    blockingLeftTurn(generateRandomTurnDelay());

  }
  else if (isLineLDetectingLine()) {
    setLEDs(0, 1, 0);
    blockingBackward(BACKWARD_MVMT_TIME_MS);
    blockingRightTurn(generateRandomTurnDelay());

  }
  else if (isObjLDetectingObject()) {
    setLEDs(0, 1, 1);
    //debouncing
    stopWheels();
    int i = 0;
    uint32_t readings[DEBOUNCING_READINGS];
    for (int i = 0; i < DEBOUNCING_READINGS; i++) {
      readings[i] = isObjLDetectingObject();
      delay(20);
    }
    quickSort(readings, DEBOUNCING_READINGS);

    if (getMedian(readings, DEBOUNCING_READINGS)) {
      startWheels();
      blockingRightTurn(250);
    }

  } else if (isObjRDetectingObject()) {
    setLEDs(0, 0, 1);
    //debouncing
    stopWheels();
    int i = 0;
    uint32_t readings[DEBOUNCING_READINGS];
    for (int i = 0; i < DEBOUNCING_READINGS; i++) {
      readings[i] = isObjRDetectingObject();
      delay(20);
    }
    quickSort(readings, DEBOUNCING_READINGS);

    if (getMedian(readings, DEBOUNCING_READINGS)) {
      startWheels();
      blockingLeftTurn(250);

    }
  }
  else if (isObjFDetectingObject()) {
    setLEDs(1, 1, 1);
    stopWheels();
    //debouncing
    int i = 0;
    uint32_t readings[DEBOUNCING_READINGS];
    for (int i = 0; i < DEBOUNCING_READINGS; i++) {
      readings[i] = isObjFDetectingObject();
      delay(20);
    }
    quickSort(readings, DEBOUNCING_READINGS);
    if (getMedian(readings, DEBOUNCING_READINGS)) {
      startWheels();
      blockingBackward(500);
      random(0, 2) == 0 ? blockingLeftTurn(800) : blockingRightTurn(800);
    }
  }
  else if (isObjFRDetectingObject()) {
    setLEDs(1, 0, 1);
    //debouncing
    stopWheels();
    int i = 0;
    uint32_t readings[DEBOUNCING_READINGS];
    for (int i = 0; i < DEBOUNCING_READINGS; i++) {
      readings[i] = isObjFRDetectingObject();
      delay(20);
    }
    quickSort(readings, DEBOUNCING_READINGS);

    if (getMedian(readings, DEBOUNCING_READINGS)) {
      startWheels();
      blockingBackward(250);
      blockingLeftTurn(800);
    }

  }
  else if (isObjFLDetectingObject()) {
    setLEDs(1, 0, 1);
    //debouncing
    stopWheels();
    int i = 0;
    uint32_t readings[DEBOUNCING_READINGS];
    for (int i = 0; i < DEBOUNCING_READINGS; i++) {
      readings[i] = isObjFLDetectingObject();
      delay(20);
    }
    quickSort(readings, DEBOUNCING_READINGS);

    if (getMedian(readings, DEBOUNCING_READINGS)) {
      startWheels();
      blockingBackward(250);
      blockingRightTurn(800);
    }
  }
  else {
    setupWheelSpeedPin(MOTOR_FREQUENCY, MOTOR_DUTY);
    forward();
    startWheels();
  }
  resetWDT();
}

long generateRandomTurnDelay() {
  return (random(50, 255) / 255.0) * ROTATION_MVMT_TIME_MS;
}

// The function 'blockingLeftTurn' instantiates snowplow left turn and an appropriate delay.
// Parameter: None.
// returns: Void
void blockingLeftTurn(long delayMs) {
  setupWheelSpeedPin(MOTOR_FREQUENCY, MOTOR_DUTY_MANEUVER);
  turnLeft();
  delay(delayMs);

}

// The function 'blockingRightTurn' instantiates snowplow right turn and an appropriate delay.
// Parameter: None.
// returns: Void
void blockingRightTurn(long delayMs) {
  setupWheelSpeedPin(MOTOR_FREQUENCY, MOTOR_DUTY_MANEUVER);
  turnRight();
  delay(delayMs);
}

// The function 'blockingBackward' instantiates snowplow backward and an appropriate delay.
// Parameter: None.
// returns: Void
void blockingBackward(long delayMs) {
  backward();
  delay(delayMs);
}

// The function 'setupLEDPins' configures the specified ports for the flags/LEDs.
// Parameter: None.
// returns: Void
void setupLEDPins() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}


// The function 'setLEDs' assigns the flags/LEDS to appropriate ports.
// Parameter: None.
// returns: Void
void setLEDs(bool red, bool blue, bool green) {
  digitalWrite(5, red);
  digitalWrite(6, blue);
  digitalWrite(7, green);
}

// The function 'resetLED' reconfigures the flags/LEDS to LOW.
// Parameter: None.
// returns: Void
void resetLEDs() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
