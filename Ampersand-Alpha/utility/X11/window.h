#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include "display.h"

namespace xcab
{
  class window
  {
    private:
      ::Window m_window;
      ::Display * m_display;
    private:
      // Disable copying
      window (const xcab::window & window) {}
      xcab::window & operator= (const xcab::window & window) {}
    public:
      window (
        ::Display * display,
        ::Window parent,
        const int x, const int y,
        const unsigned int width, const unsigned int height,
        const unsigned int borderWidth,
        const unsigned long border,
        const unsigned long background) : m_display(display)
      {
        m_window = XCreateSimpleWindow(display, parent, x, y, width, height, borderWidth, border, background);
      }

      window (
        ::Display * display,
        ::Window parent,
        const int x, const int y,
        const unsigned int width, const unsigned int height,
        const unsigned int borderWidth,
        const int depth,
        const unsigned int type,
        Visual * visual,
        const unsigned long valueMask,
        XSetWindowAttributes * attributes) : m_display(display)
      {
        m_window = XCreateWindow(display, parent, x, y, width, height, borderWidth, depth, type, visual, valueMask, attributes);
      }

      ~window ()
      {
        XDestroyWindow(m_display, m_window);
      }

      operator ::Window () const
      {
        return m_window;
      }

      void show ()
      {
        XMapWindow(m_display, m_window);
        XFlush(m_display);
        return;
      }
  };
};

#endif
