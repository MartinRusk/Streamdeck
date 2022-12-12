#include <Arduino.h>
#include "but.h"

#define DEBOUNCE 100

But::But(uint8_t p)
{
    pin = p;
    pinMode(pin, INPUT_PULLUP);
    state = false;
    lastState = false;
}

void But::handle()
{
    lastState = state;
    bool input = digitalRead(pin);
    if (!input)
    {
        state = true;
        timer = millis() + DEBOUNCE;
    }
    else
    {
        if (millis() > timer)
        {
            state = false;
        }
    }
}

bool But::isPressed(void)
{
    handle();
    return (state && !lastState);
}

bool But::isReleased(void)
{
    return (!state && lastState);
}
