#include <Servo.h>

#define BUTTON_PIN 9
#define SERVO_PIN 10

int servoBasePosition = 0;
int servoEndPosition = 180;

Servo servo;
int buttonPushed = 0;

void setup() {
  servo.attach(SERVO_PIN);
  moveServo(servoBasePosition);
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW){
    buttonPushed = 1;
  }

  if(buttonPushed){
    moveServoWithDelay(servoEndPosition);
    delay(3000);
    moveServoWithDelay(servoBasePosition);
    buttonPushed = 0;
  }

}

void moveServo(int position){
    servo.write(position); 
}

void moveServoWithDelay(int position){
    moveServo(position);
    delay(100); //Ждем, пока серва доедет до нужной позиции
}
