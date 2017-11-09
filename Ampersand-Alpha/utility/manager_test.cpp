#include "keyboardmanager.h"
#include "timemanager.h"
#include "bash.h"
#include "vector.h"
#include <iostream>

using namespace std;

int main ()
{
  // Managers
  TimeManager time;
  KeyboardManager keyboard("/dev/input/event0");
  keyboard.init();

  // Testing stuff
  Vector<2> oldPosition;
  Vector<2> position;
  double speed = 10.0;

  cout << "HERE WE GO..." << endl;
  sleep(1);
  cout << term::CLEAR << term::cursor_hide() << term::cursor_move_to(0, 0) << "&" << flush;

  while (true)
  {
    time.update();
    if (keyboard.get_key_state(KEY_ESC))
    {
      keyboard.terminate(27);
      break;
    }
    if (keyboard.get_key_state(KEY_A))
    {
      position -= Vector<2>(speed, 0.0) * time.get_delta_time();
    }
    if (keyboard.get_key_state(KEY_D))
    {
      position += Vector<2>(speed, 0.0) * time.get_delta_time();
    }
    if (keyboard.get_key_state(KEY_S))
    {
      position += Vector<2>(0.0, speed) * time.get_delta_time();
    }
    if (keyboard.get_key_state(KEY_W))
    {
      position -= Vector<2>(0.0, speed) * time.get_delta_time();
    }
    if (position.get_component(0) < 0.0)
    {
      position.set_component(0, 0.0);
    }
    if (position.get_component(1) < 0.0)
    {
      position.set_component(1, 0.0);
    }
    if ((int)position.get_component(0) != (int)oldPosition.get_component(0) ||
        (int)position.get_component(1) != (int)oldPosition.get_component(1))
    {
      cout << term::cursor_move_to(position.get_component(1), position.get_component(0)) << "&";
      cout << term::cursor_move_to(oldPosition.get_component(1), oldPosition.get_component(0)) << " " << flush;
      oldPosition = position;
    }
  }
  cout << term::cursor_show() << term::CLEAR << term::cursor_move_to(0, 0);
  return 0;
}

