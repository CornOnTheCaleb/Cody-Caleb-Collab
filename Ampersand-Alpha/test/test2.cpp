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
  while(ch != 8)
  {
    if((ch = getch()) != ERR)
      cout << ch << endl;
  }
  endwin();
  
  return 0;
}
