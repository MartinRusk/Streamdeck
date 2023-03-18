#include <Arduino.h>
#include <HID-Project.h>
#include "keys.h"

#define DELAY 100

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

void Key_WA(const char *k)
{
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_ALT);
    Key(k);
    Keyboard.releaseAll();
    delay(DELAY);
}