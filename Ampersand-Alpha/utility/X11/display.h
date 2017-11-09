#ifndef DISPLAY_H
#define DISPLAY_H

#include <X11/Xlib.h>

namespace xcab
{
  class display
  {
    private:
      ::Display * m_display;
    public:
      display (const char * name)
      {
        m_display = XOpenDisplay(name);
        if (m_display == NULL)
        {
          // TODO: Throw a better exception
          throw "Unable to open display";
        }
      }

      ~display ()
      {
        XCloseDisplay(m_display);
        m_display = NULL;
      }

      operator ::Display * () const
      {
        return m_display;
      }
  };  
};

#endif
