#include <Servo.h>
#include "button.h"

#define buttonPin 1
#define servoPin 2

Servo myservo;
Button buttonOn(buttonPin);

void setup() 
{
  myservo.attach(servoPin);
  myservo.write(0);
}

void loop() {
  if (buttonOn.wasPressed())
  {
    myservo.write(90);
    delay(3000);
    myservo.write(0);
  }
}
