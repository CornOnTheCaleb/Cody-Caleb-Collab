#include <curses.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  char input;
  char grid[50][50];

  for(int y = 0; y <= 50; y++)
  {
    for(int x = 0; x <= 50; x++)
    {
      if(x == 0 || y == 0 || x == 50 || y == 50)
        grid[y][x] = '=';
      else
        grid[y][x] = ' ';
    }
  }
  for(int y = 0; y <= 50; y++)
  {
    for(int x = 0; x <= 50; x++)
    {
      cout << grid[y][x];
      if(x == 50)
        cout << endl;
    }
  }
  endwin();
  
  return 0;
}
