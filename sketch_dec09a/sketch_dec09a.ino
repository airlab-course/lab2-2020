#include "Ultrasonic.h" 
#include <Servo.h>

Servo servo;  
Ultrasonic ultrasonic(12,11); //trigPin - 12; echoPin - 11;

void setup() {  
  Serial.begin(9600);
  servo.attach(9);  
  servo.write(150); //Дефолтное значение серво
  }
 
void loop() { //в покое - 150, удар - 90
  if (ultrasonic.Ranging(CM) < 6){
  servo.write(90);
  delay(500);
  servo.write(150);
  delay(500);
  } 
}
