#include "SparkFunLSM6DSO.h"
#include "Wire.h"
#include <Servo.h>

// define pin connections
int edfPin = 9;
byte potPin = A0;

// low pass filter alpha value
float alpha = 0.2;

// create edf and IMU objects
Servo edf;
LSM6DSO myIMU;  //I2C, ADDR 0x6B

void setup() {
  Serial.begin(9600);
  // setup sensor
  pinMode(edfPin, OUTPUT);
  // Wire.begin();
  // delay(10);

  // if (myIMU.begin())
  //   Serial.println("Ready.");
  // else {
  //   Serial.println("Could not connect to IMU.");
  //   Serial.println("Freezing");
  // }

  // if (myIMU.initialize(BASIC_SETTINGS))
  //   Serial.println("Loaded Settings.");

  //setup EDF
  edf.attach(edfPin);
  edf.writeMicroseconds(1500);

  delay(5000);
  // put your setup code here, to run once:s
}

void loop() {
  edf.writeMicroseconds(1400);

  Serial.print(", Z = ");
  Serial.println(myIMU.readFloatAccelZ(), 3);
  delay(5);
}

// Low-pass filter function with linearity compensation
int filter(int val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return int(filteredValue);
}
