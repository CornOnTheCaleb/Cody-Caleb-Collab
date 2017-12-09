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
    int fromX = 1, toX = world.WORLD_WIDTH, fromY = 1, toY = world.WORLD_LENGTH;
    bool smart = true;
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
      if (input.get_key_state(XK_Up))
      {
        if ((input.get_key_state(XK_Shift_L) || input.get_key_state(XK_Shift_R)) && fromY < toY)
        {
          ++fromY;
          smart = false;
        }
        else if (fromY > 1)
        {
          --fromY;
          smart = false;
        }
      }
      if (input.get_key_state(XK_Down))
      {
        if ((input.get_key_state(XK_Shift_L) || input.get_key_state(XK_Shift_R)) && toY > fromY)
        {
          --toY;
          smart = false;
        }
        else if (toY < world.WORLD_LENGTH)
        {
          ++toY;
          smart = false;
        }
      }
      if (input.get_key_state(XK_Left))
      {
        if ((input.get_key_state(XK_Shift_L) || input.get_key_state(XK_Shift_R)) && fromX < toX)
        {
          ++fromX;
          smart = false;
        }
        else if (fromX > 1)
        {
          --fromX;
          smart = false;
        }
      }
      if (input.get_key_state(XK_Right))
      {
        if ((input.get_key_state(XK_Shift_L) || input.get_key_state(XK_Shift_R)) && toX > fromX)
        {
          --toX;
          smart = false;
        }
        else if (toX < world.WORLD_WIDTH)
        {
          ++toX;
          smart = false;
        }
      }
      
      float mouseX = input.get_mouse_x_pos();
      float mouseY = input.get_mouse_y_pos() - Y_OFFSET;
      int x = ((float)terminalWidth / attr.width) * mouseX;
      int y = ((float)terminalHeight / (attr.height - Y_OFFSET)) * mouseY;
      x = x + fromX + 1;
      y = y + fromY + 1;

      if (x <= world.WORLD_WIDTH - 1 && y <= world.WORLD_LENGTH && x >= 2 && y >= 2)
      {
        if (input.get_key_state(XK_1))
        {
          world.insert(x, y, GRASS);
        }
        else if (input.get_key_state(XK_2))
        {
          world.insert(x, y, AIR);
        }
        else if (input.get_key_state(XK_3))
        {
          world.insert(x, y, CLOUD);
        }
      }
      
      if (!smart)
      {
        cout << term::cursor_move_to(1, 1) << term::CLEAR << flush;
      }
      toX = (toX > terminalWidth ? terminalWidth : toX);
      toY = (toY > terminalHeight ? terminalHeight : toY);
      print.print(world, 1, 1, fromX, toX, fromY, toY, smart);
      smart = true;
    
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
        cout << "world: " << "(" << fromX << ", " << fromY << ") (" << toX << ", " << toY << ")" << endl;
      }
    }
    input.flush_stdin_until(27);
  }
  string response;
  cout << term::cursor_move_to(1, 1) << term::CLEAR << term::cursor_show() << "Save? (y/n): " << flush;
  cin >> response;
  if (response.find("y") != string::npos || response.find("Y") != string::npos)
  {
    cout << term::cursor_move_to(1, 1) << term::CLEAR << "Save as: " << flush;
    cin >> response;
    if (response.length() > 0)
    {
      ofstream file(response.c_str());
      file << world.WORLD_LENGTH << " " << world.WORLD_WIDTH << endl;
      for (int i = 1; i <= world.WORLD_LENGTH; ++i)
      {
        for (int j = 1; j <= world.WORLD_WIDTH; ++j)
        {
          file << world.map[i][j] << endl;
        }
      }
      file.close();
    }
  }
  cout << term::normal_terminal() << flush;
  return 0;
}
