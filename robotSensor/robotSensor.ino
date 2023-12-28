#include <Servo.h>
#include <SoftwareSerial.h>
#include <time.h>

Servo myservo;
SoftwareSerial BTserial(8, 9);  // RX | TX

time_t now;
volatile int DL;
volatile int DM;
volatile int DR;

int inputDelay = 12;
int outputDelay = 13;
int inputServo = 10;

int currentkeyboard = 0;
int controlSpeed = 90;
boolean currentkeyboardFlag = false;

void setup() {
  DL = 0;
  DM = 0;
  DR = 0;

  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);

  myservo.attach(inputServo);
  myservo.write(90);

  Serial.begin(9600);
}

void loop() {
  DM = UltrasonicSensor();

  if (DM != 0 && DM < 15) {
    stopp();
    currentkeyboardFlag = false;
  } else {
    if (!currentkeyboardFlag) {
      controlByKeyboard();
    }
  }

  if (Serial.available()) {
    controlByKeyboard();
  }
}

float UltrasonicSensor() {
  // Serial.println("UltrasonicSensor : function");
  digitalWrite(inputDelay, LOW);
  delayMicroseconds(2);
  digitalWrite(inputDelay, HIGH);
  delayMicroseconds(10);
  digitalWrite(inputDelay, LOW);
  float distance = pulseIn(outputDelay, HIGH) / 58.00;
  Serial.print(DM);
  Serial.println("cm");
  delay(1000);
  return distance;
}

float controlServo(int data) {
  Serial.println("controlServo : function");
  // digitalWrite(inputServo, HIGH);
  delayMicroseconds(1000);
  myservo.write(data);
  delayMicroseconds(5000);
  // digitalWrite(inputServo, LOW);
}

void controlByKeyboard() {
  currentkeyboardFlag = true;
  int key = currentkeyboard;

  if (Serial.available()) {
    key = Serial.read();
    currentkeyboard = key;
  }

  Serial.println(key);

  switch (key) {

      // STOP ==================
    case (32):
      Serial.println("stopp");
      stopp();
      break;

    case (48):
      Serial.println("stopp");
      stopp();
      break;

    case (53):
      Serial.println("stopp");
      stopp();
      break;
      // STOP ==================

      // FORWARD =================
    case 56:
      Serial.println("forward");
      forward(controlSpeed, controlSpeed);
      break;
      // FORWARD =================

      // BACKWARD =================
    case 50:
      Serial.println("backward");
      backward(controlSpeed, controlSpeed);
      break;
      // BACKWARD =================

      // ROTATELEFT =================
    case 52:
      Serial.println("rotateLeft");
      rotateLeft(controlSpeed, controlSpeed);
      break;
      // ROTATELEFT =================

      // ROTATERIGHT =================
    case 54:
      Serial.println("rotateRight");
      rotateRight(controlSpeed, controlSpeed);
      break;
      // ROTATERIGHT =================
  }
  // }
}

void forward(int a, int b) {
  digitalWrite(2, LOW);
  analogWrite(5, a);
  digitalWrite(4, HIGH);
  analogWrite(6, b);
}

void backward(int a, int b) {
  digitalWrite(2, HIGH);
  analogWrite(5, a);
  digitalWrite(4, LOW);
  analogWrite(6, b);
}

void rotateRight(int a, int b) {
  digitalWrite(2, HIGH);
  analogWrite(5, a);
  digitalWrite(4, HIGH);
  analogWrite(6, b);
}

void rotateLeft(int a, int b) {
  digitalWrite(2, LOW);
  analogWrite(5, a);
  digitalWrite(4, LOW);
  analogWrite(6, b);
}

void stopp() {
  digitalWrite(2, HIGH);
  analogWrite(5, 0);
  digitalWrite(4, LOW);
  analogWrite(6, 0);
}
