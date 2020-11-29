#include <Servo.h>
#include "button.h"

#define PIN_BUTTON_ON 9
#define SERVO_PIN 10

Servo servo;
Button buttonOn(PIN_BUTTON_ON)

void setup() {
  servo.attach(SERVO_PIN);
}

void loop() {
  if (buttonOn.wasPressed())
  {
    moveServo(180);
    delay(3000);
    moveServo(0);   
  }
}

void moveServo(int position){
    servo.write(position); 
}
