#include <iostream>
#include <unistd.h>
#include "timemanager.h"

using namespace std;

int main ()
{
  TimeManager time;
  time.update();
  sleep(5);
  time.update();
  cout << time.get_delta_time() << endl;
}
