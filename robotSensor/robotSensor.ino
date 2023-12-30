#include <Servo.h>
#include <SoftwareSerial.h>
#include <time.h>
#include <IRremote.h>

Servo myservo;
SoftwareSerial BTserial(8, 9);  // RX | TX

long ir_rec;

IRrecv irrecv(3);
decode_results results;

time_t now;
volatile int DL;
volatile int DM;
volatile int DR;

int inputDelay = 12;
int outputDelay = 13;
int inputServo = 10;

int currentkeyboard = 0;
int controlSpeed = 100;
bool flag = true;
bool currentkeyboardFlag = false;
long currentRemote = 0;

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

  irrecv.enableIRIn();

  Serial.begin(9600);
}

void loop() {
  DM = UltrasonicSensor();

  if (DM != 0 && DM < 15) {
    stopp();
    currentkeyboardFlag = false;
  } else {
    if (!currentkeyboardFlag) {
      controlByRemote();
    }
  }

  if (irrecv.decode(&results)) {
    controlByRemote();
  }
  // if (Serial.available()) {
  //   controlByKeyboard();
  // }
}

float UltrasonicSensor() {
  // Serial.println("UltrasonicSensor : function");
  digitalWrite(inputDelay, LOW);
  delayMicroseconds(2);
  digitalWrite(inputDelay, HIGH);
  delayMicroseconds(10);
  digitalWrite(inputDelay, LOW);
  float distance = pulseIn(outputDelay, HIGH) / 58.00;
  // Serial.print(DM);
  // Serial.println("cm");
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
      forward();
      break;
      // FORWARD =================

      // BACKWARD =================
    case 50:
      Serial.println("backward");
      backward();
      break;
      // BACKWARD =================

      // ROTATELEFT =================
    case 52:
      Serial.println("rotateLeft");
      rotate_left();
      break;
      // ROTATELEFT =================

      // ROTATERIGHT =================
    case 54:
      Serial.println("rotateRight");
      rotate_right();
      break;
      // ROTATERIGHT =================
  }
  // }
}

void controlByRemote() {
  // Serial.println("controlByRemote : function");
  ir_rec = currentRemote;
  if (irrecv.decode(&results)) {
    currentkeyboardFlag = true;
    ir_rec = results.value;
    Serial.println(String(ir_rec));
    currentRemote = ir_rec;
    irrecv.resume();
  }



  if (flag == true) {
    if (ir_rec == 0xFF629D) {
      forward();
      Serial.println("forward");
    }
    if (ir_rec == 0xFFA857) {
      backward();
      Serial.println("backward");
    }
    if (ir_rec == 0xFF22DD) {
      turn_left();
      Serial.println("turn_left");
    }
    if (ir_rec == 0xFFC23D) {
      turn_right();
      Serial.println("turn_right");
    }
    if (ir_rec == 0xFF30CF) {
      rotate_left();
      Serial.println("rotate_left");
    }
    if (ir_rec == 0xFF7A85) {
      rotate_right();
      Serial.println("rotate_right");
    }
    if (ir_rec == 0xFF02FD) {
      stopp();
      Serial.println("stopp");
    }
  }
}

void forward() {
  flag = false;
  digitalWrite(2, LOW);
  analogWrite(5, 200);
  digitalWrite(4, HIGH);
  analogWrite(6, 200);
  flag = true;
}

void backward() {
  flag = false;
  digitalWrite(2, HIGH);
  analogWrite(5, 200);
  digitalWrite(4, LOW);
  analogWrite(6, 200);
  flag = true;
}

void turn_left() {
  flag = false;
  digitalWrite(2, LOW);
  analogWrite(5, 200);
  digitalWrite(4, HIGH);
  analogWrite(6, 100);
  flag = true;
}

void turn_right() {
  flag = false;
  digitalWrite(2, LOW);
  analogWrite(5, 100);
  digitalWrite(4, HIGH);
  analogWrite(6, 200);
  flag = true;
}
void rotate_left() {
  flag = false;
  digitalWrite(2, HIGH);
  analogWrite(5, 200);
  digitalWrite(4, HIGH);
  analogWrite(6, 200);
  flag = true;
}


void rotate_right() {
  digitalWrite(2, LOW);
  analogWrite(5, 200);
  digitalWrite(4, LOW);
  analogWrite(6, 200);
}



void stopp() {
  digitalWrite(2, HIGH);
  analogWrite(5, 0);
  digitalWrite(4, LOW);
  analogWrite(6, 0);
}
