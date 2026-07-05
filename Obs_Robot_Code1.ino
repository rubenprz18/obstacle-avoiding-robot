The code you created: #include <NewPing.h>
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 7
#define STOP_DISTANCE 20

#define SPEEDL 215
#define SPEEDR 180

#define TURN_DURATION 300

#define TURN_SPEED_L 170
#define TURN_SPEED_R 150
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
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
  analogWrite(ENA, SPEEDL);
  analogWrite(ENB, SPEEDR);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void moveBackward() {
  kickstart();
  analogWrite(ENA, SPEEDL);
  analogWrite(ENB, SPEEDR);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void turnRight() {
  kickstart();
  analogWrite(ENA, TURN_SPEED_L);
  analogWrite(ENB, TURN_SPEED_R);
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
  if (distance == 0 || distance > STOP_DISTANCE) {
    moveForward();
  } else {
    stopMotors();
    delay(300);
    moveBackward();
    delay(500);
    turnRight();
    delay(TURN_DURATION);
    stopMotors();
  }
}