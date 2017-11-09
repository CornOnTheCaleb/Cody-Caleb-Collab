#include <iostream>
#include "keyboardmanager.h"

int main (int argc, char ** argv)
{
  KeyboardManager keyboard("/dev/input/event0");
  keyboard.init();
  while (true)
  {
    if (keyboard.get_key_state(KEY_ESC))
    {
      keyboard.terminate(27);
      break;
    }
    else
    {
      // DO STUFF    
    }
  }
  return 0;
}
