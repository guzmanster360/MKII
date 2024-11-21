// # Included libraries
#include "SparkFunLSM6DSO.h"
#include "Wire.h"
#include <Servo.h>

// Pin Connections for Hardware
int edfPin = 10; // EDF IO Pin
byte potPin = A6; // Potentiometer Connection Pin (Used only during manual control)

// PID Controller Values
double kp = 15; // Proportinal control coefficient
double ki = 20; // Integral control coefficient
double kd = 0.00; // Derivative control coefficient

// Define variables for PID control
double setpoint = 0;  // Target value for the Z-axis reading
double input, output; // input/output variables
double integral, prev_error; // integral/previous error variables

double pos_x = 0;
double pos_y = 0;
double pos_z = 0;

double vel_x = 0;
double vel_y = 0;
double vel_z = 0;



// low pass filter alpha value
float alpha = 0.2; // used for smoothing potentiometer output

// Create edf and IMU objects
Servo edf;
LSM6DSO myIMU;  //Default constructor is I2C, addr 0x6B


void setup() {
  Serial.begin(115200); // Serial Monitor Beginning
  // setup sensor
  pinMode(edfPin, OUTPUT);
  edf.attach(edfPin);

  // IMU Initialization
  Wire.begin();
  delay(10);

  if (myIMU.begin())
    Serial.println("Ready.");
  else {
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if (myIMU.initialize(BASIC_SETTINGS))
    Serial.println("Loaded Settings.");

  // ARM EDF
  // Wait for ESC to initialize
  delay(5000);  // 5 seconds delay for initialization
  edf.writeMicroseconds(1000);
  delay(5000);
  edf.writeMicroseconds(2000);
  delay(5000);
  
  // Calibration complete
  Serial.println("ESC calibration complete.");

  // Initialize values to zero
  integral = 0;
  prev_error = 0;
}

void loop() {
 
  // POTENTIOMETER CONTROL (FOR MANUAL CONTROL ONLY)
  // int potVal = filter(analogRead(potPin));
  // int pwm = map(potVal, 0, 1023, 1100, 2400);
  // Serial.println(pwm);
  // edf.writeMicroseconds(pwm);

  input = myIMU.readFloatAccelZ() - 1; // create input variable with 1g offset

  double error = setpoint - input; // calculate error
  integral += error; // increase the integral value by the calculated error every iteration

  double derivative = error - prev_error; // calculate derivative term

  output = kp * error + ki * integral + kd * derivative; // calculate output based off PID coefficients defined earlier

  prev_error = error; // store error for next iteration

  // Console Output

  adjustThrust(output);
  Serial.print(", Error: ");
  Serial.print(error);
  Serial.print(", Input: ");
  Serial.print(input);
  Serial.print(", Output: ");
  Serial.println(output);

  Serial.print(" Z = ");
  Serial.println(myIMU.readFloatAccelZ(), 3);
  delay(10);
}

void adjustThrust(double output) {
  // Convert PID output to EDF control signal (e.g., PWM signal)
  // Example: Map the output to a PWM duty cycle
  int dutyCycle = map(output, -255, 255, 1100, 1900);

  // Update EDF control signal
  Serial.print("DC: ");
  Serial.print(dutyCycle);
  edf.writeMicroseconds(dutyCycle);
}

// Low-pass filter function with linearity compensation
int filter(int val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return int(filteredValue);
}
