#include <iostream>
#include "keyboardmanager.h"

int main (int argc, char ** argv)
{
  KeyboardManager keyboard("/dev/input/event0");
  /*keyboard.init();
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
  }*/
  while (true)
  {
    char c = keyboard.getch();
    if (c > 0) cout << c << endl;
  }
  return 0;
}
