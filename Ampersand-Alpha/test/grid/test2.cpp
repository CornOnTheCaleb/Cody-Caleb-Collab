#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  char grid[50][50];

  for(int y = 0; y < 50; y++)
  {
    for(int x = 0; x < 50; x++)
    {
      if(x == 0 || y == 0 || x == 49 || y == 49)
        grid[y][x] = '=';
      else
        grid[y][x] = ' ';
    }
  }
  for(int y = 0; y < 50; y++)
  {
    for(int x = 0; x < 50; x++)
    {
      cout << grid[y][x];
      if(x == 49)
        cout << endl;
    }
  }

  return 0;
}
