#ifndef PRINT_MANAGER_H
#define PRINT_MANAGER_H

#include "terminalmanager.h"
#include "../map.h"

class PrintManager
{
  private:
    World m_previous;
    bool m_hasPrinted;
  public:
    PrintManager () : m_hasPrinted(false) {}
    void smart_print (const World & world, const int column, const int line)
    {
      for (int y = 1; y <= world.WORLD_LENGTH; ++y)
      {
        for (int x = 1; x <= world.WORLD_WIDTH; ++x)
        {
          if (m_hasPrinted)
          {
            if (world.map[y][x] != m_previous.map[y][x])
            {
              cout << term::cursor_move_to(line + y, column + x) << world.map[y][x];
            }
          }
          else
          {
            string temp = world.map[y][x];
            cout << term::cursor_move_to(line + y, column + x) << temp << endl;
          }
          m_previous.map[y][x] = world.map[y][x];
        }
      }
      m_hasPrinted = true;
      // m_previous = world;
    }
};

#endif
