#ifndef But_h
#define But_h

#include <Arduino.h>

// simple button handler
class But
{
private:
    uint8_t pin;
    bool state;
    bool lastState;
    unsigned long timer;
    void handle();

public:
    But(uint8_t pin);
    // handle button and return positive edge
    bool isPressed(void);
    // return negative edge (needs inPressed() as prerequisite)
    bool isReleased(void);
};

#endif
