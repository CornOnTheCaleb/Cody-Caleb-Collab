#include "bash.h"
#include "keyboard.h"
#include "timemanager.h"
#include "vector.h"

using namespace std;

int main ()
{
  TimeManager time;
  Vector<2> oldPosition(0.0, 0.0);
  Vector<2> position(0.0, 0.0);
  Vector<2> velocity(0.0, 0.0);
  Vector<2> acceleration(0.0, -9.8);
  bool quit = false;
  bool moveRight = false;
  cout << term::CLEAR;
  nonblock(true);
  while (!quit)
  {
    time.update();
    char c = getch();
    switch (c)
    {
      case 27:
        quit = true;
        break;
      case ' ':
        velocity += Vector<2>(0.0, 10.0);
        break;
      case 'd':
        moveRight = true;
        break;
      default:
        if (c > 0)
        {
          cout << term::cursor_move_to(0, 0) << c;
        }
    }
    if (moveRight)
    {
      velocity.set_component(0, 500.0);
    }
    cout << time.get_delta_time() << endl;
    velocity += acceleration * time.get_delta_time();
    position += velocity * time.get_delta_time();
    if (moveRight)
    {
      moveRight = false;
      velocity.set_component(0, 0.0);
    }
    if (position.get_component(1) < 0)
    {
      position.set_component(1, 0.0);
      velocity.set_component(1, 0.0);
    }
    if ((int)oldPosition.get_component(1) != (int)position.get_component(1) ||
        (int)oldPosition.get_component(0) != (int)position.get_component(0))
      cout << term::cursor_move_to(oldPosition.get_component(1), oldPosition.get_component(0)) << " ";
      cout << term::cursor_move_to(position.get_component(1), position.get_component(0)) << "O";
    oldPosition = position;
  }
  nonblock(false);
  return 0;
}
