
// Green -> 3v3 (CCW)
// Yellow -> A0 (W)
// Red -> GND (CW)

int blade_rot = 60;  //deg
int rot_range = (1023 / (360 / blade_rot));

// ENCODER VALUES
int L_up_min = 764;
int L_up_max = 767;

int L_down_min = 112;
int L_down_max = 112;

int R_up = 1014;
int R_down = 72;
int R_FA_UP = 559;
int L_FA_UP = 469;
int R_FA_DOWN = 0;
int L_FA_DOWN = 0;

int values[200] = {};
int i = 0;
int val1 = 0;
int val2 = 0;
bool direction = false;

float alpha = 0.5;

void setup() {
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  val1 = analogRead(A0);
  // Serial.println(val1);
  Serial.println(filter(val1));
  // values[i] = filter(val1);
  // i += 1;

  // if (i == 200) {
  //   long sum = 0L;  // sum will be larger than an item, long for safety.
  //   for (int j = 0; j < 200; j++) {
  //     sum += values[j];
  //   }
  //     Serial.println("min: " + min(values));
  //     delay(10000);
  // }
  // direction = (feedback_loop(val1, direction));
  // Serial.println(direction);
  // delay(15);
}

// Low-pass filter function with linearity compensation
int filter(int val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return int(filteredValue);
}
