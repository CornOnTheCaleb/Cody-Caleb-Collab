#include <iostream>
#include <fstream>
#include "utility/terminalmanager.h"
#include "utility/inputmanager.h"
#include "utility/timemanager.h"
#include "utility/printmanager.h"
#include "map.h"

using namespace std;

const int Y_OFFSET = 90;

int main (int argc, char ** argv)
{
  World world;
  {
    InputManager input;
    TimeManager time;
    PrintManager print;
    cout << term::alternate_terminal() << term::cursor_hide() << flush;
    int terminalWidth, terminalHeight;
    while (true)
    {
      input.update();
      time.update();
      term::get_dimensions(terminalWidth, terminalHeight);
      if (input.get_key_state(XK_Escape))
      {
        break;
      }
      XWindowAttributes attr = input.get_window_attributes();
      float mouseX = input.get_mouse_x_pos();
      float mouseY = input.get_mouse_y_pos() - Y_OFFSET;
      int x = ((float)terminalWidth / attr.width) * mouseX;
      int y = ((float)terminalHeight / (attr.height - Y_OFFSET)) * mouseY;
      if (x + 2 <= world.WORLD_WIDTH && y + 2 <= world.WORLD_LENGTH)
      {
        if (input.get_key_state(XK_1))
        {
          world.insert(x + 2, y + 2, GRASS);
        }
        else if (input.get_key_state(XK_2))
        {
          world.insert(x + 2, y + 2, AIR);
        }
        else if (input.get_key_state(XK_3))
        {
          world.insert(x + 2, y + 2, CLOUD);
        }
        else if (input.get_key_state(XK_Up))
        {
          
        }
      }
      print.print(world, 0, 0, true);
    
      bool debug = false;
      if (debug)
      {
        cout << term::cursor_move_to(56, 1) << "Delta time: " << time.get_delta_time() << term::CLEAR_LINE << endl;
        cout << "mouse: (" << mouseX << ", " << mouseY << ")" << term::CLEAR_LINE << endl;
        cout << "screen: (" << attr.width << ", " << attr.height << ")" << term::CLEAR_LINE << endl;
        cout << "ratio x: " << (float)mouseX / attr.width << term::CLEAR_LINE << endl;
        cout << "ratio y: " << (float)mouseY / attr.height << term::CLEAR_LINE << endl;
        cout << "cursor: (" << x << ", " << y << ")" << term::CLEAR_LINE << endl;
        cout << "terminal: (" << terminalWidth << ", " << terminalHeight << ")" << term::CLEAR_LINE << endl;
        cout << "ratio x: " << (float)x / terminalWidth << term::CLEAR_LINE << endl;
        cout << "ratio y: " << (float)y / terminalHeight << term::CLEAR_LINE << endl;
      }
    }
    input.flush_stdin_until(27);
  }
  cout << term::cursor_move_to(1, 1) << term::CLEAR << term::cursor_show() << "Save as: " << flush;
  string line;
  cin >> line;
  ofstream file(line.c_str());
  file << world.WORLD_LENGTH << " " << world.WORLD_WIDTH << endl;
  for (int i = 1; i <= world.WORLD_LENGTH; ++i)
  {
    for (int j = 1; j <= world.WORLD_WIDTH; ++j)
    {
      file << world.map[i][j] << endl;
    }
  }
  file.close();
  cout << term::normal_terminal() << flush;
  return 0;
}
