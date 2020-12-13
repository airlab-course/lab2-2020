#include <Servo.h>

const int ECHO_PIN = 8;
const int TRIG_PIN = 9;
const int SERVO_PIN = 4;

const float cm_per_mks = 0.017;

Servo radarServo;

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  radarServo.attach(SERVO_PIN);

  Serial.begin(115200);
}

void loop() {
  int i = 1;
  int dir = 1;
  
  while (i != 0) {
    radarServo.write(i);
    
    if (i % 5 == 0) {
      Serial.print(measureDist());
      Serial.print("; ");
      Serial.println(i);
    }
    
    if (i == 180)
      dir = -1;
      
    i += dir;
    delay(50);
  }
}

unsigned long measureDist() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  return  duration * cm_per_mks;
}
