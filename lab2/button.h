#pragma once

class Button
{
public:
    Button(int _pin)
    {
        pin = _pin;
        pinMode(pin, INPUT_PULLUP);
    }

    bool isDown()
    {
        return digitalRead(pin) == HIGH;
    }

private:
    int pin;
};
