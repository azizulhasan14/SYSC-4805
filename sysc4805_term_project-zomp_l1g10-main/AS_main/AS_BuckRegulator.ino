// Pin declaration for the Buck regulator.
#define BUCK_REGULATOR_READ_PIN A11

// Configuring the buck regulator pin.
void setupBuckRegulatorPin() {
  pinMode(BUCK_REGULATOR_READ_PIN, INPUT);
}

// The function 'checkBuckRegulator' montitors the buck regulator reading. If the reading is below the desired value
// an error message is displayed.
void checkBuckRegulator() {
  float reading = 3.3 * analogRead(BUCK_REGULATOR_READ_PIN) / 1024;
  if (reading < 2.6) {
    printf("[ERROR]: buck regulator voltage low: %.1fV\n", reading);
  }
}
