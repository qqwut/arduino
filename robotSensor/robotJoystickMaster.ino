
// JoyStick
int X = A0;
int joyXValue = 0;

int Y = A1;
int joyYValue = 0;

// Motor Y ========
const int FW_Y = 9;
const int RW_Y = 10;

// Motor X ========
const int FW_X = 5;
const int RW_X = 6;

int motorSpeed = 0;

void setup() {
  Serial.begin(9600);

  pinMode(FW_Y, OUTPUT);
  pinMode(RW_Y, OUTPUT);
  pinMode(FW_X, OUTPUT);
  pinMode(RW_X, OUTPUT);
}

void loop() {

  joyXValue = analogRead(X);
  joyYValue = analogRead(Y);

  // X 
  if (joyXValue >= 515) {
    Serial.println("=== FW ===");
    int scaledValue = map(joyXValue, 515, 1023, 0, 255);
    analogWrite(RW_X, 0);
    analogWrite(FW_X, scaledValue);

    Serial.print(" X : ");
    Serial.print(joyXValue);
    Serial.print(" out = ");
    Serial.print(scaledValue);
    Serial.println("\t");

  } else if (joyXValue < 508) {
    Serial.println("=== RW ===");
    int scaledValue1 = map((joyXValue), 508, 0, 0,255);
    analogWrite(FW_X, 0);
    analogWrite(RW_X, scaledValue1);

    Serial.print(" X : ");
    Serial.print(joyXValue);
    Serial.print(" xxxx = ");
    Serial.print(scaledValue1);
    Serial.println("\t");

  } else {
    Serial.println("=== STOP ===");
    analogWrite(FW_X, 0);
    analogWrite(RW_X, 0);

    Serial.print(" X : ");
    Serial.print(joyXValue);
    Serial.println("\t");
  }

  // Y
  if (joyYValue > 515) {
    Serial.println("=== FW ===");
    int scaledValue = map((joyYValue), 513, 1024, 0, 255);
    analogWrite(RW_Y, 0);
    analogWrite(FW_Y, scaledValue);

    Serial.print(" Y : ");
    Serial.print(joyYValue);
    Serial.print(" out = ");
    Serial.print(scaledValue);
    Serial.println("\t");

  } else if (joyYValue < 508) {
    Serial.println("=== RW ===");
    int scaledValue = map((joyYValue), 508, 0, 0, 255);
    analogWrite(FW_Y, 0);
    analogWrite(RW_Y, scaledValue);

    Serial.print(" Y : ");
    Serial.print(joyYValue);
    Serial.print(" xxxx = ");
    Serial.print(scaledValue);
    Serial.println("\t");

  } else {
    Serial.println("=== STOP ===");
    analogWrite(FW_Y, 0);
    analogWrite(RW_Y, 0);
  }

  //delay(1000);
}