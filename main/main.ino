#include <Servo.h>

#define MAXA 180
#define MINA 0
#define SERVO_STEP 18

int middleValue(int minimum, int maximum){
  return (maximum + minimum) / 2.0;
}

Servo baseServo;
int currentBaseServo = middleValue(MINA, MAXA);
Servo tiltServo;
int currentTiltServo = middleValue(MINA, MAXA);

const byte width = 4;
const byte height = 4;

char keyMatrix[width][height] = {
  {'N', 'U',    'N',  'N'},
  {'L', 'N',  'R', 'N'},
  {'N', 'D',  'N',  'N'},
  {'N', 'N',  'N',  'N'}
};

static bool keyDownMatrix[width][height];

byte rowPins[width] = { 5, 4, 3, 2 };
byte colPins[height] = { 6, 7, 8, 9 };

void setup() {
  baseServo.attach(10);
  tiltServo.attach(11);
  updatePositions();

  initPins(rowPins, OUTPUT, width);
  initPins(colPins, INPUT, height);
  
  Serial.begin(115200);
}

void initPins(byte* pins, int value, int length){
	for (int i = 0; i < length; i++) {
		pinMode(pins[i], value);
		digitalWrite(pins[i], HIGH);
  }
}

void loop() {
  char key = getKey();
  setAngle(key);
  updatePositions();
}

void setAngle(char key) {
  if (key == 'U')
    currentBaseServo = safeChangeValue(currentBaseServo + SERVO_STEP);
  else if (key == 'D')
    currentBaseServo = safeChangeValue(currentBaseServo - SERVO_STEP);
  else if (key == 'R')
    currentTiltServo = safeChangeValue(currentTiltServo + SERVO_STEP);
  else if (key == 'L')
    currentTiltServo = safeChangeValue(currentTiltServo - SERVO_STEP);
}

int safeChangeValue(int value) {
  return value >= MAXA ? MAXA : value <= MINA ? MINA : value;
}

char getKey()
{
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      bool isDown = iskeyDown(i, j);
      if (!keyDownMatrix[i][j] && isDown) {
        return keyMatrix[i][j];
      }
      keyDownMatrix[i][j] = isDown;
    } 
  }
  return 'N';
}

bool iskeyDown(int i, int j)
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
    baseServo.write(currentBaseServo);
    tiltServo.write(currentTiltServo);
    Serial.print("moving to: ");
    Serial.print(currentBaseServo);
    Serial.print(" ");
    Serial.println(currentTiltServo);
}
