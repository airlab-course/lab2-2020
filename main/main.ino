#include <Servo.h>

#define MAX_ANGLE 180
#define MIN_ANGLE 0
#define STEP 10

int get_median(int minimum, int maximum){
  return (maximum + minimum) / 2.0;
}

Servo baseServo;
int baseServoPosition = get_median(MIN_ANGLE, MAX_ANGLE);
Servo tiltServo;
int tiltServoPosition = get_median(MIN_ANGLE, MAX_ANGLE);

const char keyUp = 'U';
const char keyDown = 'D';
const char keyRight = 'R';
const char keyLeft = 'L';
const char keyNone = 'N';

const byte rowAmount = 4;
const byte colAmount = 4;

char keyMatrix[rowAmount][colAmount] = {
  {keyNone, keyUp,    keyNone,  keyNone},
  {keyLeft, keyNone,  keyRight, keyNone},
  {keyNone, keyDown,  keyNone,  keyNone},
  {keyNone, keyNone,  keyNone,  keyNone}
};

static bool keyDownMatrix[rowAmount][colAmount];

byte rowPins[rowAmount] = { 5, 4, 3, 2 };
byte colPins[colAmount] = { 6, 7, 8, 9 };

void setup() {
  baseServo.attach(10);
  tiltServo.attach(11);
  updatePositions();
 
  for (int i = 0; i < rowAmount; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  for (int i = 0; i < colAmount; i++) {
    pinMode(colPins[i], INPUT);
    digitalWrite(colPins[i], HIGH);
  }
  Serial.begin(115200);
}

void loop() {
  char key = getKey();
  setAngle(key);
  updatePositions();
}

void setAngle(char key){
  if (key == keyUp)
    baseServoPosition = safeIncrease(baseServoPosition);
  if (key == keyDown)
    baseServoPosition = safeDecrease(baseServoPosition);
  if (key == keyRight)
    tiltServoPosition = safeIncrease(tiltServoPosition);
  if (key == keyLeft)
    tiltServoPosition = safeDecrease(tiltServoPosition);
}

int safeIncrease(int value){
  return value >= MAX_ANGLE ? value : value + STEP;
}

int safeDecrease(int value){
  return value <= MIN_ANGLE ? value : value - STEP;
}

char getKey()
{
  char result = keyNone;
  for (int i = 0; i < rowAmount; i++) {
    for (int j = 0; j < colAmount; j++) {
      bool isDown = isKeyDown(i, j);
      if (!keyDownMatrix[i][j] && isDown) {
        result = keyMatrix[i][j];
      }
      keyDownMatrix[i][j] = isDown;
    } 
  }
  return result;
}

bool isKeyDown(int i, int j)
{
  bool result = false;
  digitalWrite(rowPins[i], LOW);
  if (digitalRead(colPins[j]) == LOW) {
    result = true;
  }
  digitalWrite(rowPins[i], HIGH);
  return result;
}

void updatePositions() {
    baseServo.write(baseServoPosition);
    tiltServo.write(tiltServoPosition);
    Serial.print("moving to: ");Serial.print(baseServoPosition);Serial.print(" ");Serial.println(tiltServoPosition);
}
