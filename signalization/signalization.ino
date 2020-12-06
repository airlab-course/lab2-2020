#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define PIN_SENSOR A0
#define PIN_BUTTON_OFF 22
#define PIN_BUZZER 24

Buzzer buzzer(PIN_BUZZER);
Button buttonOff(PIN_BUTTON_OFF);

int notes[] = {NOTE_A4, NOTE_SILENCE};
double durations[] = {8, 4};
int melodyLength = 2;

void setup() 
{
  pinMode(PIN_SENSOR, INPUT);
  buzzer.setMelody(notes, durations, melodyLength);
}

void loop() 
{
  double dist = readDistFilter(PIN_SENSOR);
  if(dist > 10 && dist < 80) // range of correct work
  {
    buzzer.turnSoundOn();
  }

  if (buttonOff.wasPressed())
  {
    buzzer.turnSoundOff();
  }
}

double readDistFilter(int pin)
{
  int iterationsCount = 12;
  double sum = 0;
  double minimal = 1e10, maximal = -1;
  for(int i = 0; i < iterationsCount; i++) 
  {  
    double tmp = readDist(pin);
    sum += tmp;
    minimal = min(minimal, tmp);
    maximal = max(maximal, tmp);
    delay(10);
  }
  sum -= minimal + maximal;
  return sum / (iterationsCount - 2);
}

double readDist(int pin)
{
  double volts = readVoltage(pin);
  return pow(14.7737/volts, 1.2134);
}

double readVoltage(int pin)
{
  return analogRead(pin) * 5.0 / 1024.0;
}
