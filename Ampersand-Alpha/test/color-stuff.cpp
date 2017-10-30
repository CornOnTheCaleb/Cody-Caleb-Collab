#include <iostream>
using namespace std;

int main()
{
  char fuck;
  char * poop = "▓";
  while(cin >> fuck)
    cout << "\x1b[38;2;255;100;0m" << poop << "\x1b[0m" << endl;
  return 0;
}
