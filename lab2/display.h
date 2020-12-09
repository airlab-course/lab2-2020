#pragma once

#include "LedControl.h"

const int boardSizeY = 8;

LedControl ledDisplay = LedControl(26, 22, 24, 1);

class Display
{
    public:
    void init()
    {
        ledDisplay.shutdown(0, false);
        ledDisplay.setIntensity(0, 10);
        clear();
    }

    void drawPoint(int x, int y)
    {
        ledDisplay.setLed(0, boardSizeY - 1 - y, x, true);
    }

    void clear()
    {
        ledDisplay.clearDisplay(0);
    }
};
