#include <Servo.h>

const int echoPin = 8;
const int trigPin = 9;

Servo speedometerServo;

const float delayBetweenMeasuresInMs = 10.0;

void setup() {
  speedometerServo.attach(10);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);

}

void loop() {
  float firstDist = readDist();
  delay(delayBetweenMeasuresInMs);
  float secondDist = readDist();

  float speedInCmPerMs = abs(secondDist - firstDist) / delayBetweenMeasuresInMs;
  float speedInKmPerHour = (speedInCmPerMs / 100000.0) * 3600000.0;

  int angleForServo = (int)constrain(speedInKmPerHour, 0, 180);
  speedometerServo.write(angleForServo);
}

float readDist()
{
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerMicrosecond = speedOfSoundMPerSec / 10000.0;
  return readPulse() * speedOfSoundCmPerMicrosecond / 2.0;
}

float readPulse()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration;
}
