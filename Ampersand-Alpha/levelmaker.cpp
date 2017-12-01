#include <iostream>
#include <fstream>
#include "terminalmanager.h"
#include "keyboardmanager.h"
#include "map.h"

using namespace std;

int main (int argc, char ** argv)
{
  KeyboardManager keyboard("/dev/input/event0");
  keyboard.init();

  cout << term::alternate_terminal() << flush;
  int terminalWidth, terminalHeight; term::get_dimensions(terminalWidth, terminalHeight);
  while (true)
  {
    if (keyboard.get_key_state(KEY_ESC))
    {
      keyboard.terminate(27);
      break;
    }
  }
  cout << term::normal_terminal() << flush;
  return 0;
}
