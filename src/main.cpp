#include <Arduino.h>
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Button.h>


#define DEBOUNCE 100
#define DELAY 100

// class Button
// {
// private:
//   int btnPin;
//   unsigned long debounceTime;
//   int previousSteadyState;
//   int lastSteadyState;
//   int currentState;
//   unsigned long nextDebounceTime;
// public:
//   Button(int pin);
//   void setDebounceTime(unsigned long time);
//   bool isPressed(void);
//   void loop(void);
// };

// Button::Button(int pin)
// {
//   btnPin = pin;
//   debounceTime = 0;
//   pinMode(btnPin, INPUT_PULLUP);
//   previousSteadyState = digitalRead(btnPin);
//   lastSteadyState = previousSteadyState;
//   nextDebounceTime = 0;
// }

// void Button::loop(void)
// {
//   currentState = digitalRead(btnPin);
//   if (millis() >= nextDebounceTime) {
//     if (currentState != previousSteadyState)
//     {
//       previousSteadyState = lastSteadyState;
//       lastSteadyState = currentState;
//       nextDebounceTime = millis() + debounceTime;
//     }
// 	}
// }

// void Button::setDebounceTime(unsigned long time)
// {
//   debounceTime = time;
// }

// bool Button::isPressed(void)
// {
//   if (previousSteadyState == HIGH && lastSteadyState == LOW)
//     return true;
//   else
//     return false;
// }

Button button0(14);
Button button1(0);
Button button2(2);
Button button3(3);
Button button4(4);
Button button5(5);
Button button6(6);
Button button7(7);
Button button8(8);
Button button9(9);
Button buttonA(10);
Button buttonB(16);

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
  button0.setDebounceTime(DEBOUNCE);
  button1.setDebounceTime(DEBOUNCE);
  button2.setDebounceTime(DEBOUNCE);
  button3.setDebounceTime(DEBOUNCE);
  button4.setDebounceTime(DEBOUNCE);
  button5.setDebounceTime(DEBOUNCE);
  button6.setDebounceTime(DEBOUNCE);
  button7.setDebounceTime(DEBOUNCE);
  button8.setDebounceTime(DEBOUNCE);
  button9.setDebounceTime(DEBOUNCE);
  buttonA.setDebounceTime(DEBOUNCE);
  buttonB.setDebounceTime(DEBOUNCE);

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
  button0.loop();
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();
  button6.loop();
  button7.loop();
  button8.loop();
  button9.loop();
  buttonA.loop();
  buttonB.loop();

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