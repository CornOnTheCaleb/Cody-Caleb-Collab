#include <ctime>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include "keyboard.h"
using namespace std;

char * const BLOCK = "▓";
char * const WALL = "║";
char * const CEILING = "═";
char * const lCEILING_CORNER = "╔";
char * const rCEILING_CORNER = "╗";
char * const lFLOOR_CORNER = "╚";
char * const rFLOOR_CORNER = "╝";

void print(char** grid[], stringstream & output)
{
  system("clear");
  output << "\033[1;1H";
  for(int y = 1; y < 50; y++)
  {
    for(int x = 1; x < 50; x++)
    {
      output << grid[y][x];
      if(x == 49)
        output << "\n";
    }
  }
  cout << output.str();
  output.str("");
}

void print_char(char* symbol, const int& x, const int& y)
{
  stringstream output;
  output << "\e[" << y << ";" << x << "H" << symbol;
  cout << output.str();
}

void move
int main()
{
  char ** grid[50];
  char x;
  stringstream output;

  for(int i = 0; i < 50; i++)
    grid[i] = new char*[50];
  for(int y = 0; y < 50; y++)
  {
    for(int x = 0; x < 50; x++)
    {
      if(x == 1 && y == 1)
        grid[y][x] = lCEILING_CORNER;
      else if(x == 1 && y == 49)
        grid[y][x] = lFLOOR_CORNER;
      else if(x == 49 && y == 1)
        grid[y][x] = rCEILING_CORNER;
      else if(x == 49 && y == 49)
        grid[y][x] = rFLOOR_CORNER;
      else if(x == 1 || x == 49)
        grid[y][x] = WALL;
      else if(y == 1 || y == 49)
        grid[y][x] = CEILING;
      else if(x != 0 && y != 0)
        grid[y][x] = " ";
    }
  }

  print(grid, output); 
  print_char("A", 2, 3);
  for(unsigned int i = 2; i < 11; i++)
    print_char("&", i, 48);

  if(cin >> x)
  {
    cout << "\e[1;1H";
    system("clear");
    return 0;
  }
}
