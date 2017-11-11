#include "character.h"
#include "utility/printmanager.h"

int main()
{
  World fuck;
  cout << "\e[?25l";
  while(true)
  {
    cout << "\e[1;1H";
    fuck.print();
    sleep(0.25);
  }
  return 0;
}
