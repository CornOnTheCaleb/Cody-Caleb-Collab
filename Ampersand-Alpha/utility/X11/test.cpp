#include <iostream>
#include "inputmanager.h"
#include "../terminalmanager.h"

using namespace std;

int main ()
{
  InputManager input;
  bool terminate = false;
  cout << term::alternate_terminal() << flush;
  while (!terminate)
  {
    input.update();
    if (input.get_key_state(XK_Escape))
    {
      terminate = true;
    }
    else
    {
      cout << "(" << input.get_mouse_x_pos() << ", " << input.get_mouse_y_pos() << ") "
        << "Left: " << input.get_mouse_left_button() << " Middle: " << input.get_mouse_middle_button() << " Right: " << input.get_mouse_right_button() << endl;
    }
  }
  cout << term::normal_terminal() << flush;
  return 0;
}
