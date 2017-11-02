#include "bash.h"
#include "keyboard.h"
#include "timemanager.h"
#include <unistd.h>

using namespace std;

int main ()
{
  TimeManager time;
  nonblock(true);
  double x = 0.0;
  double y = 0.0;
  double v = 0.0;
  double a = -9.8;
  bool quit = false;
  cout << term::CLEAR;
  while (!quit)
  {
    time.update();
    char c = getch();
    switch (c)
    {
      case 27:
        quit = true;
        break;
      case 32:
        v += 10.0;
    }
    v = v + a * time.get_delta_time();
    y += v * time.get_delta_time();
    if (y < 0)
    {
      y = 0.0;
      v = 0.0;
    }
    if ((int)x != (int)y)
      cout << term::cursor_move_to(x, 30) << " ";
      cout << term::cursor_move_to(y, 30) << "O";
    x = y;
  }
  nonblock(false);
  return 0;
}
