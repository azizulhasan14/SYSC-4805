// The following code defines the ports used by the four wheels of the robot
#define WHEEL_BL_DIRECTION_PIN 47 // M1 RED to B
#define WHEEL_FL_DIRECTION_PIN 49 // M2 RED to B
#define WHEEL_FR_DIRECTION_PIN 53 // M4 RED to A
#define WHEEL_BR_DIRECTION_PIN 51 // M3 RED to A
// The following codes define the settings for wheel forward and reverse
#define FORWARD 1
#define BACKWARD 0

// The function 'setupWheelDirectionPins' configures the pin declarations for the wheel.
// Parameter: None.
// Returns: Void.
void setupWheelDirectionPins()
{
  pinMode(WHEEL_BL_DIRECTION_PIN, OUTPUT);
  pinMode(WHEEL_FL_DIRECTION_PIN, OUTPUT);
  pinMode(WHEEL_FR_DIRECTION_PIN, OUTPUT);
  pinMode(WHEEL_BR_DIRECTION_PIN, OUTPUT);
}

// The function 'setupWheelSpeedPin' sets PMC signal according to parameters to control the speed of wheels
// Parameter: int freq, float duty.
// Returns: Void.
void setupWheelSpeedPin(int freq, float duty)
{// PWM pin 35

  // PWM MOTOR SIGNAL SETUP
  PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
  PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
  PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);//Set PWM clock 1MHz (Mck/84)
  PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
                                | PWM_CMR_CPOL; //Set output polarity be high.
  
  int _freq = 1000000 / freq;
  
  PWM->PWM_CH_NUM[0].PWM_CPRD = _freq - 1; //Set PWM freq 1MHz/(60000) = 16.667Hz, set to 60k to get 16.66 Hz
  PWM->PWM_CH_NUM[0].PWM_CDTY = (int)(_freq / duty) - 1; // Set PWM duty cycle
}

// The function 'turnRight' makes the robot turn right by setting the left wheel of the
//  robot to move forward and the right wheel to move backward.
// Parameter: None.
// Returns: Void.
void turnRight()
{
  digitalWrite(WHEEL_FL_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_BL_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_FR_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_BR_DIRECTION_PIN, BACKWARD);
}

// The function 'turnLeft' makes the robot turn left by setting the right wheel of the
//  robot to move forward and the left wheel to move backward.
// Parameter: None.
// Returns: Void.
void turnLeft()
{
  digitalWrite(WHEEL_FL_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_BL_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_FR_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_BR_DIRECTION_PIN, FORWARD);
}

// The function 'forward' makes the robot move forward by setting all the wheels of the robot to rotate forward.
// Parameter: None.
// Returns: Void.
void forward()
{
  digitalWrite(WHEEL_BL_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_FL_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_FR_DIRECTION_PIN, FORWARD);
  digitalWrite(WHEEL_BR_DIRECTION_PIN, FORWARD);
}

// The function 'backward' makes the robot backward by setting all the wheels of the robot to rotate backward.
// Parameter: None.
// Returns: Void.
void backward()
{
  digitalWrite(WHEEL_BL_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_FL_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_FR_DIRECTION_PIN, BACKWARD);
  digitalWrite(WHEEL_BR_DIRECTION_PIN, BACKWARD);
}

// The function 'stopWheels' calls the backward function to make the robot move backward,
//  and then stops the PWM signal to make the robot stop moving.
// Parameter: None.
// Returns: Void.
void stopWheels()
{
  backward();
  PWM->PWM_DIS = PWM_DIS_CHID0;
}

// The function 'startWheels' makes the robot start to move by turning on the PWM signal.
// Parameter: None.
// Returns: Void.
void startWheels()
{
  PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel 
}