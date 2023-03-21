#include <Arduino.h>
#include <HID-Project.h>
#include <keys.h>
#include <XPLDevices.h>

// buttons as static instances
Button butMic(14);
Button butCam(0);
Button butShare(2);
Button butHand(3);
Button butVolDn(4);
Button butVolUp(5);
Button butAnswer(6);
Button butHangup(7);
Button butMode1(8);
Button butMode2(9);
Button butMode3(10);
Button butMode4(16);

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
    
    // start XPLDirect driver
    Serial.begin(XPLDIRECT_BAUDRATE);
    XP.begin("Streamdeck");

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
    // handle XPLDirect interface
    XP.xloop();

    // handle buttons
    butMic.handle();
    butCam.handle();
    butShare.handle();
    butHand.handle();
    butVolDn.handle();
    butVolUp.handle();
    butAnswer.handle();
    butHangup.handle();
    butMode1.handle();
    butMode2.handle();
    butMode3.handle();
    butMode4.handle();

    // microphone button
    if (butMic.pressed())
    {
        switch (mode)
        {
        case teams:
            Key_WA("k");
            // Key_SC("m");
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
    if (butCam.pressed())
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
    if (butShare.pressed())
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
    if (butHand.pressed())
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
    if (butVolDn.pressed())
    {
        Consumer.press(MEDIA_VOLUME_DOWN);
    }
    if (butVolDn.released())
    {
        Consumer.release(MEDIA_VOLUME_DOWN);
    }

    // volume up button
    if (butVolUp.pressed())
    {
        Consumer.press(MEDIA_VOLUME_UP);
    }
    if (butVolUp.released())
    {
        Consumer.release(MEDIA_VOLUME_UP);
    }

    // accept call button
    if (butAnswer.pressed())
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
    if (butHangup.pressed())
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
    if (butMode1.pressed())
    {
        set_mode(teams);
    }

    // Zoom button
    if (butMode2.pressed())
    {
        set_mode(zoom);
    }

    // WebEx button
    if (butMode3.pressed())
    {
        set_mode(webex);
    }

    // Windows button
    if (butMode4.pressed())
    {
        set_mode(none);
    }
}