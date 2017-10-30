#include <curses.h>
#include <iostream>
using namespace std;

int main()
{
  initscr();
  cbreak();
  noecho();
  int ch;
  nodelay(stdscr, TRUE);
  while(ch != 4)
  {
    ch = getch();
    if(ch != -1)
      cout << ch;
  }
  endwin();
  
  return 0;
}
