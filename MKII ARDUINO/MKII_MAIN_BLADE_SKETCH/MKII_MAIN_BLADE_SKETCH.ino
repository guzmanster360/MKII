#define IN1 11
#define IN2 12
#define EN1 10
#define BF 9
#define BB 8
#define B1 7

bool dir = false;
int speed = 255;

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(BF, INPUT);
  pinMode(BB, INPUT);
  pinMode(B1, INPUT);

  while (digitalRead(BB) != HIGH) {
    analogWrite(EN1, speed);
    digitalWrite(IN1, LOW);  //Blade Back
    digitalWrite(IN2, HIGH);
    Serial.println("S1");
  }
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(B1) == HIGH) {
    dir = move(dir);
  }
}

bool move(bool dir) {

  if (dir == false) {
    while (digitalRead(BF) != HIGH) {
      analogWrite(EN1, speed);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("S2");
    }
    stop();
    return true;

  }


  else {
    while (digitalRead(BB) != HIGH) {
      analogWrite(EN1, speed);
      digitalWrite(IN1, LOW);  //Forward
      digitalWrite(IN2, HIGH);
      Serial.println("S3");
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
