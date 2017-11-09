#include <X11/Xlib.h>
#include <unistd.h>
#include "display.h"
#include "window.h"

int main ()
{
  xcab::display display(NULL);
  xcab::window window(display, XDefaultRootWindow(display), 0, 0, 200, 100, 0, 0, 0);
  window.show();
  sleep(5);
  return 0;
}
