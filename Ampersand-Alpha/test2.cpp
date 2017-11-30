#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
  ifstream file("first_try.txt");
  if (file.is_open())
  {
    string test;
    file >> test >> test;
    cout << test << endl;
    file.close();
  }
  return 0;
}
