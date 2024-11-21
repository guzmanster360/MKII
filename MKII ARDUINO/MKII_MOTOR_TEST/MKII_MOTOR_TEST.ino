/*
  DRV8833-Dual-Motor-Driver-Module
  made on 23 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/

#define AIN1 12
#define AIN2 11
#define BIN1 9
#define BIN2 10
#define POTL A0

int blade_rot = 60; //deg
int rot_range = (1023/blade_rot);
int val1 = 0;
int val2 = val1;

void setup() {
  Serial.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(POTL, OUTPUT);


}

void loop() {
  

}

void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}

void set_motor_currents(int pwm_A, int pwm_B)
{
  set_motor_pwm(pwm_A, AIN1, AIN2);
  set_motor_pwm(pwm_B, BIN1, BIN2);

  // Print a status message to the console.
  Serial.print("Set motor A PWM = ");
  Serial.print(pwm_A);
  Serial.print(" motor B PWM = ");
  Serial.println(pwm_B);
}

int spin_and_wait(int pwm_A, int pwm_B, int duration) {
  set_motor_currents(pwm_A, pwm_B);

  delay(duration);
  
}
