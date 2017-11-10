#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "display.h"
#include "window.h"
#include <iostream>

using namespace std;

int main ()
{
  xcab::display display(NULL);
  xcab::window window(display, XDefaultRootWindow(display), 0, 0, 200, 100, 0, 0, 0);
  window.show();
  XSelectInput(display, window, KeyPressMask | KeyReleaseMask);
  XEvent report;
  cout << "Entering loop" << endl;
  while (true)
  {
    XNextEvent(display, &report);
    switch (report.type)
    {
      case KeyPress:
      {
        char buf[11];
        KeySym keysym;
        XComposeStatus status;
        int count = XLookupString (&report.xkey, buf, 10, &keysym, &status);
        buf[count] = 0;
        cout << keysym << " " << buf << " " << report.xkey.state << endl;
        break;
      }
      default:
      {
        cout << "Other" << endl;
        break;
      }
    }
  }
  sleep(5);
  return 0;
}
