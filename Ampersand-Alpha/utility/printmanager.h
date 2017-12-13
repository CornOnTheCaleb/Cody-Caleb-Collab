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
    void print (const World & world, const int column, const int line, const bool smart)
    {
      print(world, column, line, 1, world.WORLD_WIDTH, 1, world.WORLD_LENGTH, smart);
    }
    void print (const World & world, const int column, const int line, const int fromX, const int toX, const int fromY, const int toY, const bool smart)
    {
      for (int y = fromY; y <= toY; ++y)
      {
        for (int x = fromX; x <= toX; ++x)
        {
          if (world.map[y][x] != "\0")
          {
            if (m_hasPrinted && smart)
            {
              if (world.map[y][x] != m_previous.map[y][x])
              {
                cout << term::cursor_move_to(line + (y - fromY), column + (x - fromX)) << world.map[y][x];
              }
            }
            else
            {
              string temp = world.map[y][x];
              cout << term::cursor_move_to(line + (y - fromY), column + (x - fromX)) << temp;
            }
          }
          m_previous.map[y][x] = world.map[y][x];
        }
      }
      cout << flush;
      m_hasPrinted = true;
      // m_previous = world;
    }
};

#endif
