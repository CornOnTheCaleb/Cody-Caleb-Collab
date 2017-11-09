#include "keyboardmanager.h"
#include <iostream>

using namespace std;

int main ()
{
  KeyboardManager keyboard("/dev/input/event0");
  while (true)
  {
    keyboard.update_keyboard_state();
    if (keyboard.get_key_state(KEY_ESC) == KEY_HELD)
    {
      break;
    }
  }
  return 0;
}

