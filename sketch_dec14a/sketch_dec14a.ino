#include <Ultrasonic.h>

#include <Servo.h> 
#include "Ultrasonic.h" 

Servo servo;
Ultrasonic ultrasonic(12,11); //trigPin  12, echoPin  11;

void setup() {  
  Serial.begin(9600);
  servo.attach(9);  // серво на 9
  servo.write(150); //по умолчанию серва в положении готовности
  }
 
void loop() {
  if (ultrasonic.Ranging(CM) < 10){
  servo.write(90); //серво бьет
  delay(500);
  servo.write(150); //вернуться в положение готовности
  delay(500); //без задержки тут её колошматит :<
  } 
 
}
