/******************************************************************************
Basic_Readings.ino

https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DSO
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DSO_Arduino_Library

Description:
Most basic example of use.

Example using the LSM6DSO with basic settings.  This sketch collects Gyro and
Accelerometer data every second, then presents it on the serial monitor.

Development environment tested:
Arduino IDE 1.8.2

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunLSM6DSO.h"
#include "Wire.h"
//#include "SPI.h"
float alpha = 0.2;

LSM6DSO myIMU;  //Default constructor is I2C, addr 0x6B

void setup() {


  Serial.begin(115200);
  delay(500);

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
}


void loop() {
  //Get all parameters
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  Serial.println(myIMU.readFloatAccelX(), 3);
  Serial.print(" Y = ");
  Serial.println(myIMU.readFloatAccelY(), 3);
  Serial.print(" Z = ");
  Serial.println(myIMU.readFloatAccelZ(), 3);

  Serial.print("\nGyroscope:\n");
  Serial.print(" X = ");
  Serial.println(myIMU.readFloatGyroX(), 3);
  Serial.print(" Y = ");
  Serial.println(myIMU.readFloatGyroY(), 3);
  Serial.print(" Z = ");
  Serial.println(myIMU.readFloatGyroZ(), 3);

  Serial.print("\nThermometer:\n");
  Serial.print(" Degrees F = ");
  Serial.println(myIMU.readTempF(), 3);

  delay(1000);
}

// Low-pass filter function with linearity compensation
float filter(float val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return float(filteredValue);
}