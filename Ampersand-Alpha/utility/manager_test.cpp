#include "keyboardmanager.h"
#include "timemanager.h"
#include <iostream>

using namespace std;

int main ()
{
  TimeManager time;
  KeyboardManager keyboard("/dev/input/event0");
  keyboard.init();
  while (true)
  {
    time.update();
    if (keyboard.get_key_state(KEY_ESC))
    {
      keyboard.terminate(27);
      break;
    }
    cout << "Hold ESC to exit..." << endl;
    cout << "Runtime: " << time.get_runtime() << endl << endl;
    sleep(1);
  }
  return 0;
}

