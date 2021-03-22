#include <Servo.h>

const int echoPin = 8;
const int trigPin = 9;

Servo servo;

void setup() {
servo.attach(10);
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);

}

void loop() {
float firstDistance = readDistance();
delay(10);
float secondDistance = readDistance();

float speedKmPerHour = abs(secondDistance - firstDistance) / 36000000.0;
int angleForServo = (int)constrain(speedKmPerHour, 0, 180);
servo.write(angleForServo);
}

float readDistance()
{
  float distance;
  long duration;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/5800000;
  return distance;
}
