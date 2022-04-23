#include <Arduino.h>
#include <Keyboard.h>
#include <KeyboardLayout.h>

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
  if (!input) {
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
  office
} mode;

void Key(const char *k)
{
  Keyboard.print(k);
  delay(DELAY);
}

void Key_S(const char *k)
{
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.print(k);
  Keyboard.release(KEY_LEFT_SHIFT);
  delay(DELAY);
}

void Key_SC(const char *k)
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.print(k);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
  delay(DELAY);
}

void Key_A(const char *k)
{
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print(k);
  Keyboard.release(KEY_LEFT_ALT);
  delay(DELAY);
}

void Key_W(const char *k)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.print(k);
  Keyboard.release(KEY_LEFT_GUI);
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
  digitalWrite(A2, !(mode == office));
  digitalWrite(A3, true);
}

void setup()
{
  Keyboard.begin();

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  digitalWrite(A0, true);
  digitalWrite(A1, true);
  digitalWrite(A2, true);
  digitalWrite(A3, true);

  set_mode(none);
}

void loop()
{
  if (button0.isPressed())
  {
    // microphone
    switch (mode)
    {
    case teams:
      Key_SC("m");
      break;
    default:
      Key_W("h");
    }
  }

  if (button1.isPressed())
  {
    // camera
    switch (mode)
    {
    case teams:
      Key_SC("o");
      break;
    default:;
    }
  }

  if (button2.isPressed())
  {
    // share screen
    switch (mode)
    {
    case teams:
      Key_SC("e");
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
    default:;
    }
  }

  if (button4.isPressed())
  {
    // volume dn
  }

  if (button5.isPressed())
  {
    // volume up
  }

  if (button6.isPressed())
  {
    // accept call
    switch (mode)
    {
    case teams:
      Key_SC("a");
      break;
    default:;
    }
  }

  if (button7.isPressed())
  {
    // hang up
    switch (mode)
    {
    case teams:
      Key_SC("d");
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
    set_mode(office);
  }

  if (buttonB.isPressed())
  {
    set_mode(none);
  }
}