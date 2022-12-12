#include <Arduino.h>
#include <HID-Project.h>
#include "but.h"
#include "keys.h"

// buttons as static instances
But button0(14);
But button1(0);
But button2(2);
But button3(3);
But button4(4);
But button5(5);
But button6(6);
But button7(7);
But button8(8);
But button9(9);
But buttonA(10);
But buttonB(16);

// modes for the key layout
enum t_mode
{
    none,
    teams,
    zoom,
    webex
} mode;

// activate the app via the position of the icon in the taskbar
void app_activate()
{
    if (mode == teams)
    {
        // must be adapted to the individual taskbar configuration
        Key_W("8");
    }
}

// activate a mode 
void set_mode(t_mode m)
{
    if (m == mode)
    {
        // if mode was already selected activate app via taskbar position
        app_activate();
    }
    else
    {
        // select new mode
        mode = m;
        digitalWrite(A0, !(mode == teams));
        digitalWrite(A1, !(mode == zoom));
        digitalWrite(A2, !(mode == webex));
        digitalWrite(A3, !(mode == none));
    }
}

// initialization
void setup()
{
    // start keyboard driver for key library and consumer driver for volume control
    Keyboard.begin();
    Consumer.begin();

    // initialize LED pins
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    digitalWrite(A0, true);
    digitalWrite(A1, true);
    digitalWrite(A2, true);
    digitalWrite(A3, true);

    // sweep LEDs to signalize initialization
    digitalWrite(A0, false);
    delay(250);
    digitalWrite(A1, false);
    delay(250);
    digitalWrite(A2, false);
    delay(250);
    digitalWrite(A3, false);
    delay(250);

    // Teams is default mode
    set_mode(teams);
}

// cyclic loop
void loop()
{
    // microphone button
    if (button0.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("m");
            break;
        case zoom:
            Key_A("a");
            break;
        case webex:
            Key_C("m");
            break;
        default:
            Key_W("h");
        }
    }

    // camera button
    if (button1.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("o");
            break;
        case zoom:
            Key_A("v");
            break;
        case webex:
            Key_SC("v");
            break;
        default:;
        }
    }

    // share screen button
    if (button2.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("e");
            break;
        case zoom:
            Key_A("s");
            break;
        case webex:
            Key_SC("d");
            break;
        default:;
        }
    }

    // raise hand button
    if (button3.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("k");
            break;
        case zoom:
            Key_A("z");
            break;
        case webex:
            Key_SC("r");
            break;
        default:;
        }
    }

    // volume down button
    if (button4.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_DOWN);
    }
    if (button4.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_DOWN);
    }

    // volume up button
    if (button5.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_UP);
    }
    if (button5.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_UP);
    }

    // accept call button
    if (button6.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("u");
            break;
        case webex:
            Key_SC("c");
            break;
        default:;
        }
    }

    // hang up button
    if (button7.isPressed())
    {
        switch (mode)
        {
        case teams:
            Key_SC("h");
            break;
        case zoom:
            Key_A("q");
            delay(100);
            Keyboard.println();
            break;
        case webex:
            Key_C("l");
            break;
        default:;
        }
    }

    // Teams button
    if (button8.isPressed())
    {
        set_mode(teams);
    }

    // Zoom button
    if (button9.isPressed())
    {
        set_mode(zoom);
    }

    // WebEx button
    if (buttonA.isPressed())
    {
        set_mode(webex);
    }

    // Windows button
    if (buttonB.isPressed())
    {
        set_mode(none);
    }
}