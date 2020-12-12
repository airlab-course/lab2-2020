#include <LedControl.h>

#define IR_PIN A0
#define ECHO_PIN 7
#define TRIG_PIN 6
#define LED_DATA_PIN 8
#define LED_CS_PIN 9
#define LED_CLK_PIN 10
#define LED_DISPLAYS_COUNT 8
#define LED_ROWS 2
#define LED_COLUMNS 4
#define LED_DISPLAY_SIZE 8
#define LED_X_PIXELS LED_COLUMNS * LED_DISPLAY_SIZE
#define LED_Y_PIXELS LED_ROWS * LED_DISPLAY_SIZE

int us_values[LED_X_PIXELS + 1];
int ir_values[LED_X_PIXELS + 1];
LedControl ledControl = LedControl(LED_DATA_PIN, LED_CLK_PIN, LED_CS_PIN, LED_DISPLAYS_COUNT);

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  for (int i = 0; i < LED_DISPLAYS_COUNT; i++) {
    ledControl.shutdown(i, false);
    ledControl.setIntensity(i, 5);
    ledControl.clearDisplay(i);
  }
}

void loop() {
  us_values[LED_X_PIXELS] = toLEDY(readDistUS());
  ir_values[LED_X_PIXELS] = toLEDY(readDistIRFiltered(5));
  for (int i = 0; i < LED_X_PIXELS; i++){
    updateLED(i, us_values);
    updateLED(i, ir_values);
  }
}

void updateLED(int i, int values[]) {
  setPixel(i, values[i], false);
  values[i] = values[i + 1];
  setPixel(i, values[i], true);
}

void setPixel(int x, int y, boolean value) {
  x = constrain(x, 0, LED_X_PIXELS - 1);
  y = constrain(y, 0, LED_Y_PIXELS - 1);
  int row = LED_ROWS - (y / LED_DISPLAY_SIZE) - 1;
  int column = x / LED_DISPLAY_SIZE;
  ledControl.setLed(
    row * LED_COLUMNS + column,
    y % LED_DISPLAY_SIZE,
    LED_DISPLAY_SIZE - (x % LED_DISPLAY_SIZE) - 1,
    value
  );
}

int toLEDY(double dist) {
  int lowerBound = 5;
  int upperBound = 70;
  return map(
    constrain(dist, lowerBound, upperBound) - lowerBound,
    0, upperBound - lowerBound - 1,
    0, LED_Y_PIXELS - 1
  );
}

double readDistIRFiltered(int itCount) {
  double sum = 0.0;
  double minimal = 10000.0;
  double maximal = -1.0;
  for (int i = 0; i < itCount; i++) {
    double current = readDistIR();
    sum += current;
    minimal = min(minimal, current);
    maximal = max(maximal, current);
    delay(10);
  }

  return (sum - minimal - maximal) / (itCount - 2.0);
}

double readDistIR() {
  double result = analogRead(IR_PIN) * 5.0 / 1024.0;
  return pow(14.7737 / result, 1.2134);
}

double readDistUS()
{
  const double speedOfSoundMPerSec = 340.0;
  const double speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readUSPulse() * speedOfSoundCmPerUs / 2.0;
}

double readUSPulse()
{
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH);
}
