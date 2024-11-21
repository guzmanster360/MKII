// Green -> 3v3 (CCW)
// Yellow -> A0 (W)
// Red -> GND (CW)

#define IN1 12
#define IN2 11
#define EN1 10
#define ENCA 9
#define ENCB 8
#define b_pin 8

int blade_rot = 60;  //deg
int rot_range = (1023 / (360 / blade_rot));

//L BLADE MOTOR CALIBRATION VALUES
int L_up_min = 764;
int L_up_max = 767;

int L_down_min = 110;
int L_down_max = 114;

//R BLADE MOTOR CALIBRATION VALUES=
int R_up = 1014;
int R_down = 72;

float alpha = 0.5;
//false = down
//true = up

int counter = 0;
int aState;
int aLastState;

void setup() {
  Serial.begin(9600);

  // pinMode(ENCA, OUTPUT);
  // pinMode(ENCB, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  delay(20);

  // Reads the initial state of the outputA
  // aLastState = digitalRead(ENCA);

  // int val1 = filter(analogRead(POTL));

  // while (val1 < L_down_min || val1 > L_down_max) {
  //   val1 = filter(analogRead(POTL));
  //   Serial.println("HERE");
  //   analogWrite(EN1, 255);
  //   digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
  //   digitalWrite(IN2, HIGH);  // set motor driver high
  //   delay(5);
  // }
  // Serial.println(val1);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void loop() {
  analogWrite(EN1, 255);
  digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
  digitalWrite(IN2, HIGH);  // set motor driver high
  delay(10);

  // aState = digitalRead(ENCA);  // Reads the "current" state of the outputA
  // Serial.println(aState);
  // // If the previous and the current state of the outputA are different, that means a Pulse has occured
  // if (aState != aLastState) {
  //   // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
  //   if (digitalRead(ENCB) != aState) {
  //     counter++;
  //   } else {
  //     counter--;
  //   }
  //   Serial.print("Position: ");
  //   Serial.println(counter);
  // }
  // aLastState = aState;  // Updates the previous state of the outputA with the current state

  //   int val1 = filter(analogRead(POTL));
  //   Serial.println(val1);
  //   // bool state = posControl(L_down_min, L_down_max, L_up_min, L_up_max);

  // }

  // bool posControl(int start_min, int start_max, int stop_min, int stop_max) {

  //   int val1 = filter(analogRead(POTL));

  //   while (val1 < start_min || val1 > start_max) {
  //     Serial.println(val1);
  //     analogWrite(EN1, 255);
  //     digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
  //     digitalWrite(IN2, HIGH);  // set motor driver high
  //     return false;
  //   }

  //   while (val1 < stop_min || val1 > stop_max) {
  //     Serial.println(val1);
  //     analogWrite(EN1, 255);
  //     digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
  //     digitalWrite(IN2, HIGH);  // set motor driver high
  //     return true;
  //   }
}

// Low-pass filter function with linearity compensation
int filter(int val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return int(filteredValue);
}
