#include <Arduino.h>
#include <HID-Project.h>

#define DEBOUNCE 100
#define DELAY 100

class But
{
private:
    uint8_t pin;
    bool state;
    bool lastState;
    unsigned long timer;

public:
    But(uint8_t pin);
    bool isPressed(void);
    bool isReleased(void);
};

But::But(uint8_t p)
{
    pin = p;
    pinMode(pin, INPUT_PULLUP);
    state = false;
    lastState = false;
}

bool But::isPressed(void)
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
            state = false;
    }
    return (state && !lastState);
}

bool But::isReleased(void)
{
    return (!state && lastState);
}

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

enum t_mode
{
    none,
    teams,
    zoom,
    webex
} mode;

void Key(const char *k)
{
    Keyboard.print(k);
    delay(DELAY);
}

void Key_S(const char *k)
{
    Keyboard.press(KEY_LEFT_SHIFT);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}

void Key_SC(const char *k)
{
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}

void Key_C(const char *k)
{
    Keyboard.press(KEY_LEFT_CTRL);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}

void Key_A(const char *k)
{
    Keyboard.press(KEY_LEFT_ALT);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}

void Key_W(const char *k)
{
    Keyboard.press(KEY_LEFT_GUI);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}

void set_mode(t_mode m)
{
    if (m == mode)
    {
        mode = none;
    }
    else
    {
        mode = m;
    }
    digitalWrite(A0, !(mode == teams));
    digitalWrite(A1, !(mode == zoom));
    digitalWrite(A2, !(mode == webex));
    digitalWrite(A3, true);
}

void setup()
{
    Keyboard.begin();
    Consumer.begin();

    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    digitalWrite(A0, true);
    digitalWrite(A1, true);
    digitalWrite(A2, true);
    digitalWrite(A3, true);

    digitalWrite(A0, false);
    delay(250);
    digitalWrite(A1, false);
    delay(250);
    digitalWrite(A2, false);
    delay(250);
    digitalWrite(A3, false);
    delay(250);

    set_mode(none);
}

void loop()
{
    // microphone
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

    // camera
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

    // share screen
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

    if (button3.isPressed())
    {
        // raise hand
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

    // Volume down
    if (button4.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_DOWN);
    }
    if (button4.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_DOWN);
    }

    // Volume up
    if (button5.isPressed())
    {
        Consumer.press(MEDIA_VOLUME_UP);
    }
    if (button5.isReleased())
    {
        Consumer.release(MEDIA_VOLUME_UP);
    }

    // accept call
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

    // hang up
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

    if (button8.isPressed())
    {
        set_mode(teams);
    }

    if (button9.isPressed())
    {
        set_mode(zoom);
    }

    if (buttonA.isPressed())
    {
        set_mode(webex);
    }

    if (buttonB.isPressed())
    {
        set_mode(none);
    }
}