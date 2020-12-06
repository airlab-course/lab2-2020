#include <Servo.h>
#include "button.h"

#define BUTTON_PIN 9
#define SERVO_PIN 10

Servo servo;
Button button(BUTTON_PIN); 

void setup() {
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop() {
  if (button.wasPressed())
  {
    servo.write(180);
    delay(3000);
    servo.write(0);
  }
}
