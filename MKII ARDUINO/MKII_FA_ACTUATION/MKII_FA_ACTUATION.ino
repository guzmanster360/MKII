// bottom link rotation: 56.479931 deg
// top link rotation: 86.479945 deg
//Yellow +
//Green -
#define r_pot A1
#define l_pot A0

#define IN1 12
#define IN2 13 // RIGHT MOTOR
#define EN1 11


#define IN3 7
#define IN4 8 // LEFT MOTOR
#define EN2 10

#define B1 9


bool open = true;

float tl_rot = 56.479931;   //deg
float bl_rot = 86.479945;   //deg
float l_length = 26.43951;  //mm
int r_closed_min = 305;
int r_closed_max = 312;
int r_open_min = 832;
int r_open_max = 832;

int l_closed_min = 829;
int l_closed_max = 832;
int l_open_min = 24;
int l_open_max = 24;


float s_ratio = tl_rot / bl_rot;
int speed = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // put your main code here, to run repeatedly:
  Serial.print((analogRead(A0)));
  Serial.print("   ");
  Serial.print((analogRead(A1))); // 
  Serial.print("   ");
  Serial.println((digitalRead(B1)));

  if (digitalRead(B1) == HIGH) {
    analogWrite(EN1, speed);
        digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
        digitalWrite(IN2, HIGH);  // set motor driver high-
        analogWrite(EN2, speed);
        digitalWrite(IN3, HIGH);   // set motor driver low (DOWN)
        digitalWrite(IN4, LOW);  // set motor driver high
        delay(150);
      }
    stop();

}

bool move(bool open) {

  if (open == false) {

    if ((analogRead(r_pot) < r_closed_min) && (analogRead(l_pot) < l_closed_min)) {
      while ((analogRead(r_pot) < r_closed_min) && (analogRead(l_pot) < l_closed_min)) {
        analogWrite(EN1, speed);
        digitalWrite(IN1, LOW);   // set motor driver low (DOWN)
        digitalWrite(IN2, HIGH);  // set motor driver high-
        analogWrite(EN2, speed);
        digitalWrite(IN3, HIGH);   // set motor driver low (DOWN)
        digitalWrite(IN4, LOW);  // set motor driver high
      }
      stop();
    }

    delay(50);

    return true;
  } else {

    if ((analogRead(r_pot) > r_open_max) && (analogRead(l_pot) > l_open_max)) {
      while ((analogRead(r_pot) > r_open_max) && (analogRead(l_pot) > l_open_max)) {
        analogWrite(EN1, speed);
        digitalWrite(IN1, HIGH);  // set motor driver low (DOWN)
        digitalWrite(IN2, LOW);   // set motor driver high
        analogWrite(EN2, speed);
        digitalWrite(IN3, LOW);  // set motor driver low (DOWN)
        digitalWrite(IN4, HIGH);   // set motor driver high
      }
      stop();
    }

    delay(50);
  }

  return false;
}

void stop() {
  analogWrite(EN1, 0);
  digitalWrite(IN1, LOW);  // set motor driver low (DOWN)
  digitalWrite(IN2, LOW);  // set motor driver high
  analogWrite(EN2, 0);
  digitalWrite(IN3, LOW);  // set motor driver low (DOWN)
  digitalWrite(IN4, LOW);  // set motor driver high
}

int rpm() {

}

