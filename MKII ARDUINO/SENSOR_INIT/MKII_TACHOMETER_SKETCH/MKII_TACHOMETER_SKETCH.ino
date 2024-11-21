#include <Servo.h>


#define read_pin A0
#define pot_pin A1

Servo bldc;
int pot;
int speed;

void setup() {
  // put your setup code here, to run once
  pinMode(7, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);

  bldc.attach(9);
  bldc.writeMicroseconds(1500);

}

void loop() {
  // put your main code here, to run repeatedly:
  pot = analogRead(A1);
  speed = map(pot, 0, 1023, 0, 1500);
  Serial.println(speed);
  bldc.writeMicroseconds(speed);
  delay(10);

}
