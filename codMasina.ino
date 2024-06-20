
#include <Servo.h>
#include <AFMotor.h>
#define Echo A4
#define Trig A5
#define turnleft A0
#define turnright A1
#define motor 10
#define Speed 255
#define spoint 60

char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(turnleft,INPUT);
  pinMode(turnright,INPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}
void loop() {
  //Obstacle();
  //Bluetoothcontrol();
  //linefollower();
 
}
void linefollower()
{
   Serial.println(digitalRead(turnleft));
   Serial.println(digitalRead(turnright));

  if(digitalRead(turnleft)==0 && digitalRead(turnright)==0){
    M1.run(FORWARD);
    M1.setSpeed(100);
    M2.run(FORWARD);
    M2.setSpeed(100);
    M3.run(FORWARD);
    M3.setSpeed(100);
    M4.run(FORWARD);
    M4.setSpeed(100);
  }
  else if(digitalRead(turnleft)==0 && !analogRead(turnright)==0){
    M1.run(FORWARD);
    M1.setSpeed(200);
    M2.run(FORWARD);
    M2.setSpeed(200);
    M3.run(BACKWARD);
    M3.setSpeed(200);
    M4.run(BACKWARD);
    M4.setSpeed(200);
  }
  else if(!digitalRead(turnleft)==0 && digitalRead(turnright)==0){
    M1.run(BACKWARD);
    M1.setSpeed(200);
    M2.run(BACKWARD);
    M2.setSpeed(200);
    M3.run(FORWARD);
    M3.setSpeed(200);
    M4.run(FORWARD);
    M4.setSpeed(200);
  }
  else if(!digitalRead(turnleft)==0 && !digitalRead(turnright)==0){
    M1.run(RELEASE);
    M1.setSpeed(0);
    M2.run(RELEASE);
    M2.setSpeed(0);
    M3.run(RELEASE);
    M3.setSpeed(0);
    M4.run(RELEASE);
    M4.setSpeed(0);
  }
}
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
}
void Obstacle() {
  distance = ultrasonic();
  if (distance <= 20) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

// Ultrasonic sensor distance reading function
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
int rightsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}
int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}

