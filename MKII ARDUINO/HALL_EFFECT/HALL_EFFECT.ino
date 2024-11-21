#define IN1 12
#define IN2 11
#define EN1 10
#define B1 9

float alpha = .75;

bool dir = true;

int up = 300;
int down = 45;
int speed = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(B1, INPUT);

  while (analogRead(A0) < up) {
    analogWrite(EN1, speed);
    digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
    digitalWrite(IN2, HIGH);  // set motor driver high
    Serial.println("S2");
  }
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(filter(analogRead(A0)));

  if (digitalRead(B1) == HIGH) {
    dir = move(dir);
  }
  delay(250);
}

// Low-pass filter function with linearity compensation
int filter(int val1) {
  static float filteredValue = 0;  // Declare filteredValue as static
  // Apply low-pass filter
  filteredValue = (alpha * val1) + ((1 - alpha) * filteredValue);
  return int(filteredValue);
}

bool move(bool dir) {


  if (dir == false) {

    if (analogRead(A0) > up) {
      while (analogRead(A0) > up) {
        analogWrite(EN1, speed);
        digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
        digitalWrite(IN2, HIGH);  // set motor driver high
        Serial.println("S1");
      }
      delay(150);
      stop();
    };

    while (analogRead(A0) < up) {
      analogWrite(EN1, speed);
      digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
      digitalWrite(IN2, HIGH);  // set motor driver high
      Serial.println("S2");
    }

    stop();

    return true;
  } else {

    if (analogRead(A0) > up) {
      while (analogRead(A0) > up) {
        analogWrite(EN1, speed);
        digitalWrite(IN1, HIGH);  // set motor driver high (UP)
        digitalWrite(IN2, LOW);   // set motor driver low
        Serial.println("S3");
      }
      delay(150);
      stop();
    };

    while (analogRead(A0) < up) {
      analogWrite(EN1, speed);
      digitalWrite(IN1, HIGH);  // set motor driver high (UP)
      digitalWrite(IN2, LOW);   // set motor driver low
      Serial.println("S4");
    }

    stop();

    return false;
  }
}

void stop() {
  analogWrite(EN1, 0);
  digitalWrite(IN1, LOW);  // set motor driver low (DOWN)
  digitalWrite(IN2, LOW);  // set motor driver high
}
