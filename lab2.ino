#include "Ultrasonic.h"
#include <Servo.h> 

Ultrasonic ultrasonic(12, 13);
Servo servo;

void setup()
{ 
  Serial.begin(9600);
  if(!servo.attached())
  {
    servo.attach(9);
  }
}

void loop()
{
  float dist_cm = ultrasonic.Ranging(CM);
  if (dist_cm < 5)
  {
    for (int pos = 0; pos <= 180; pos += 10)
    {
      servo.write(pos);
      delay(15);
    }
    for (int pos = 180; pos >= 0; pos -= 10)
    {
      servo.write(pos);
      delay(15);
    }
  }
}
