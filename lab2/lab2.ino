#include "button.h"
#include "display.h"
#include <Servo.h>

Button hitButton(2);
Display powerDisplay;
Servo hitServo;

int powerLevelMultiplier = 25;
int powerLevelMax = 7;

void setup()
{
    powerDisplay.init();
    hitServo.attach(9);
    hitServo.write(0);
}

void loop()
{
    if (hitButton.isDown())
    {
        int power = measurePower();
        makeHit(power);
        showPower(power);
    }
}

void makeHit(int power)
{
    int angle = (int)(power * (180 / powerLevelMax));
    hitServo.write(angle);
    delay(100);
    hitServo.write(0);
}

int measurePower()
{
    unsigned long pressTime = measurePressTime();
    return constrain((int)(pressTime / powerLevelMultiplier), 0, powerLevelMax);
}

unsigned long measurePressTime()
{
    unsigned long start = millis();
    while (true)
    {
        if (!hitButton.isDown())
        {
            return millis() - start;
        }
    }
}

void showPower(int power)
{
    powerDisplay.clear();
    for (int i = 0; i < power; i++)
    {
        powerDisplay.drawPoint(i, 0);
    }
}
