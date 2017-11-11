#include <fstream>
#include <iostream>
#include <string>
#include "utility/terminalmanager.h"
#include "character.h"
using namespace std;

int main()
{
  ifstream fin;
  string input;

  fin.open("tmp.txt");

  fin >> input;

  for(int i = 0; i < input.size(); i++)
  {
    if(input[i] == '1')
      cout << rCEILING_CORNER << endl;
    else if(input[i] == '2')
      cout << lCEILING_CORNER << endl;
    else if(input[i] == '8')
      cout << CEILING << endl;
    else if(input[i] == '4')
      cout << WALL << endl;
    else if(input[i] == 'a')
      cout << AIR << endl;
    else if(input[i] == 'c')
      cout << CLOUD << endl;
    else if(input[i] == 'g')
      cout << GRASS << endl;
  }

  return 0;
}
