#include "printmanager.h"

const char * const FUCK = "▓";

int main ()
{
  PrintManager printer;
  World world;
  string s = world.map[world.WORLD_LENGTH][1];
  cout << "From world: " << s << endl;
  string t = FUCK;
  cout << "Straight outta compton: " << t << endl;
  return 0;
}
