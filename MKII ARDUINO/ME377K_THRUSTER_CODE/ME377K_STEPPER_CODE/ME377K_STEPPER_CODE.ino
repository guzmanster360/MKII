#define STEP_PIN 8   // Step pin connected to Arduino digital pin 2
#define DIR_PIN 9    // Direction pin connected to Arduino digital pin 3

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
}

void loop() {
  digitalWrite(DIR_PIN, HIGH);  // Set direction to clockwise
  for (int i = 0; i < 200; i++) {  // 200 steps for one revolution
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);  // Adjust this delay as needed for your motor's speed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);  // Adjust this delay as needed for your motor's speed
  }
  delay(1000);
  digitalWrite(DIR_PIN, LOW);  // Set direction to clockwise
  for (int i = 0; i < 200; i++) {  // 200 steps for one revolution
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);  // Adjust this delay as needed for your motor's speed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);  // Adjust this delay as needed for your motor's speed
  }
  delay(1000);
}


