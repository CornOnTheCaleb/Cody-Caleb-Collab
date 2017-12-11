#include <iostream>
#include <fstream>
#include <vector>
#include "utility/terminalmanager.h"
#include "utility/inputmanager.h"
#include "utility/timemanager.h"
#include "utility/printmanager.h"
#include "utility/calibrationmanager.h"
#include "map.h"

using namespace std;

vector< pair< vector< vector<int> >, string > > MATERIAL_KEY_COMBOS =
{
  {{{XK_1}}, GRASS},
  {{{XK_2}}, CLOUD},
  {{{XK_3}}, AIR},
  {{{XK_w}, {XK_s}}, CEILING},
  {{{XK_a}, {XK_d}}, WALL},
  {{{XK_w, XK_a}}, lCEILING_CORNER},
  {{{XK_w, XK_d}}, rCEILING_CORNER},
  {{{XK_s, XK_a}}, lFLOOR_CORNER},
  {{{XK_s, XK_d}}, rFLOOR_CORNER},
};

int main (int argc, char ** argv)
{
  World world;
  string response;
  cout << "Load world from file (y/n) ";
  cin >> response;
  if (response == "y" || response == "Y")
  {
    cout << "File: ";
    cin >> response;
    world = World(response);
  }
  else if (response == "n" || response == "N")
  {
    int width, length;
    cout << "World dimension (width then length): ";
    cin >> width >> length;

    string fill;
    cout << "Fill world with: ";
    cin >> fill;

    world = World(width, length, fill);
  }

  cout << term::alternate_terminal() << term::cursor_hide() << flush;

  CalibrationManager calibrator;

  {
    InputManager input;
    PrintManager print;
    
    calibrator.calibrate(input);
    
    int prevTerminalWidth, prevTerminalHeight;
    int terminalWidth, terminalHeight;
    int fromX = 1, toX = world.WORLD_WIDTH, fromY = 1, toY = world.WORLD_LENGTH;
    bool smart = true;
    bool activeDraw = false;
    bool shiftedView = false;
    int prevKeysPressed = 0;
    int prevCursorX = 0, prevCursorY = 0;
    while (true)
    {
      input.update();
      term::get_dimensions(terminalWidth, terminalHeight);
      if (input.get_key_state(XK_Escape))
      {
        break;
      }
      XWindowAttributes attr = input.get_window_attributes();
      if (!shiftedView)
      {
        if (input.get_key_state(XK_Up) && fromY > 1)
        {
          --fromY;
          --toY;
          shiftedView = false;
        }
        if (input.get_key_state(XK_Down) && toY < world.WORLD_LENGTH)
        {
          ++fromY;
          ++toY;
          shiftedView = false;
        }
        if (input.get_key_state(XK_Left) && fromX > 1)
        {
          --fromX;
          --toX;
          shiftedView = false;
        }
        if (input.get_key_state(XK_Right) && toX < world.WORLD_WIDTH)
        {
          ++fromX;
          ++toX;
          shiftedView = false;
        }
        if (shiftedView)
        {
          smart = false;
        }
      }
      if (terminalWidth >= world.WORLD_WIDTH && !smart)
      {
        fromX = 1;
        toX = world.WORLD_WIDTH;
        smart = false;
      }
      if (terminalHeight >= world.WORLD_LENGTH && !smart)
      {
        fromY = 1;
        toY = world.WORLD_LENGTH;
        smart = false;
      }
      if (toX - fromX > terminalWidth)
      {
        toX = fromX + terminalWidth - 1;
        smart = false;
        if (toX > world.WORLD_WIDTH)
        {
          toX = world.WORLD_WIDTH;
          smart = false;
        }
      }
      if (toY - fromY > terminalHeight)
      {
        toY = fromY + terminalHeight - 1;
        smart = false;
        if (toY > world.WORLD_LENGTH)
        {
          toY = world.WORLD_LENGTH;
          smart = false;
        }
      }
      double mouseX = input.get_mouse_x_pos();
      double mouseY = input.get_mouse_y_pos();
      int x = calibrator.convert_x(mouseX) + fromX - 1;
      int y = calibrator.convert_y(mouseY) + fromY - 1;
      if (prevCursorX != x || prevCursorY != y)
      {
        activeDraw = false;
      }

      if (x <= world.WORLD_WIDTH && y <= world.WORLD_LENGTH && x >= 1 && y >= 1)
      {
        vector< pair<string, int> > possible;
        for (int i = 0; i < MATERIAL_KEY_COMBOS.size(); ++i)
        {
          for (int j = 0; j < MATERIAL_KEY_COMBOS[i].first.size(); ++j)
          {
            bool allPressed = true;
            for (int k = 0; k < MATERIAL_KEY_COMBOS[i].first[j].size() && allPressed; ++k)
            {
              if (!input.get_key_state(MATERIAL_KEY_COMBOS[i].first[j][k]))
              {
                allPressed = false;
              }
            }
            if (allPressed)
            {
              possible.push_back({MATERIAL_KEY_COMBOS[i].second, MATERIAL_KEY_COMBOS[i].first[j].size()});
            }
          }
        }
        if (possible.size() > 0)
        {
          string material;
          int maxPressed = 0;
          for (int i = 0; i < possible.size(); ++i)
          {
            if (possible[i].second > maxPressed)
            {
              material = possible[i].first;
              maxPressed = possible[i].second;
            }
          }
          if (!activeDraw || maxPressed > prevKeysPressed)
          {
            world.insert(x, y, material);
            activeDraw = true;
            prevKeysPressed = maxPressed;
          }
        }
        else
        {
          activeDraw = false;
        }
      }
      
      if (!smart)
      {
        cout << term::cursor_move_to(1, 1) << term::CLEAR << flush;
      }
      print.print(world, 1, 1, fromX, toX, fromY, toY, smart);
      smart = true;
      prevCursorX = x;
      prevCursorY = y;
      prevTerminalWidth = terminalWidth;
      prevTerminalHeight = terminalHeight;
    }
    input.flush_stdin_until(27);
  }
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
