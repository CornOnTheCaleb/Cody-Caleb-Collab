#include <ctime>
#include <iostream>
#include <unistd.h>
#include <sstream>
using namespace std;

void print(char** grid[], stringstream & output)
{
  output << "\033[1;1H";
  for(int y = 0; y < 50; y++)
  {
    for(int x = 0; x < 50; x++)
    {
      output << grid[y][x];
      if(x == 49)
        output << "\n";
    }
  }
  cout << output.str();
  output.str("");
}

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
      if(y == 1 || y == 49)
        grid[y][x] = "=";
      else if(x == 0 || x == 49)
        grid[y][x] = "|";
      else
        grid[y][x] = " ";
    }
  }

  clock_t start_time = clock(), stop_time, tmp;
  sleep(1);
  stop_time = clock();
  cout << (stop_time - start_time) / static_cast<float>CLOCKS_PER_SEC << endl;
  cout << static_cast<float>CLOCKS_PER_SEC << endl;

  while(true == true)
  {
    sleep(.025);
    print(grid, output);
  }

  return 0;
}
