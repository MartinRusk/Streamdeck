#include <Arduino.h>
#include <HID-Project.h>
#include "but.h"
#include "keys.h"

// buttons as static instances
But butMic(14);
But butCam(0);
But butShare(2);
But butHand(3);
But butVolDn(4);
But butVolUp(5);
But butAnswer(6);
But butHangup(7);
But butMode1(8);
But butMode2(9);
But butMode3(10);
But butMode4(16);

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
    if (butMic.isPressed())
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
    if (butCam.isPressed())
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
    if (butShare.isPressed())
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
    if (butHand.isPressed())
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
    if (butVolDn.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_DOWN);
    }
    if (butVolDn.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_DOWN);
    }

    // volume up button
    if (butVolUp.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_UP);
    }
    if (butVolUp.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_UP);
    }

    // accept call button
    if (butAnswer.isPressed())
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
    if (butHangup.isPressed())
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
    if (butMode1.isPressed())
    {
        set_mode(teams);
    }

    // Zoom button
    if (butMode2.isPressed())
    {
        set_mode(zoom);
    }

    // WebEx button
    if (butMode3.isPressed())
    {
        set_mode(webex);
    }

    // Windows button
    if (butMode4.isPressed())
    {
        set_mode(none);
    }
}