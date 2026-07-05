#include <NewPing.h>

#define TrigPin 9
#define EchoPin 10
#define maxDist 200
#define stopDistance 20
NewPing sonar(TrigPin, EchoPin, maxDist);

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 7

#define speedL 215
#define speedR 180

#define turnSpeedL 170
#define turnSpeedR 150

#define turnDuration 300

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void kickstart() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  delay(80);
}

void moveForward() {
  kickstart();
  analogWrite(ENA, speedL);
  analogWrite(ENB, speedR);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  kickstart();
  analogWrite(ENA, speedL);
  analogWrite(ENB, speedR);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnRight() {
  kickstart();
  analogWrite(ENA, turnSpeedL);
  analogWrite(ENB, turnSpeedR);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void loop() {

  delay(50);
  int distance = sonar.ping_cm();

  if (distance == 0 || distance > stopDistance) {
    moveForward();
  }
  else {
    stopMotors();
    delay(300);
    moveBackward();
    delay(500);
    turnRight();
    delay(turnDuration);
    stopMotors();
  }
}