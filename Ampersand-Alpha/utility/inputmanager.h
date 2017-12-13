#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/input.h>

enum INPUT_STATUS
{
  PRESS,
  REPEAT,
  RELEASE,
  INACTIVE
};

class InputManager
{
  public:
    Display * m_display;
    Window m_window;
    XWindowAttributes m_windowAttributes;
    char m_keyboard[32];
    INPUT_STATUS m_keyboardStatus[256];
    INPUT_STATUS m_leftMouseButtonStatus;
    INPUT_STATUS m_middleMouseButtonStatus;
    INPUT_STATUS m_rightMouseButtonStatus;
    int m_mouseXPos;
    int m_mouseYPos;
    unsigned int m_mouseButtonMask;
  private:
    void set_block_state (const bool state)
    {
      termios ttystate;
      tcgetattr(STDIN_FILENO, &ttystate);
      if (state == false)
      {
        ttystate.c_lflag &= (~ICANON & ~ECHO);
        ttystate.c_cc[VMIN] = 1;
      }
      else if (state == true)
      {
        ttystate.c_lflag |= ICANON | ECHO;
      }
      tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

      return;
    }
  private:
    void inactivate_input ()
    {
      for (int i = 0; i < 256; ++i)
      {
        m_keyboardStatus[i] = INACTIVE;
      }
      m_leftMouseButtonStatus = INACTIVE;
      m_middleMouseButtonStatus = INACTIVE;
      m_rightMouseButtonStatus = INACTIVE;
    }
    void update_input_status (INPUT_STATUS & status, const int active)
    {
      if (active)
      {
        if (status == INACTIVE || status == RELEASE)
        {
          status = PRESS;
        }
        else if (status == PRESS)
        {
          status = REPEAT;
        }
      }
      else
      {
        if (status == PRESS || status == REPEAT)
        {
          status = RELEASE;
        }
        else if (status == RELEASE)
        {
          status = INACTIVE;
        }
      }
    }
  public:
    InputManager ()
    {
      m_display = XOpenDisplay(0);
      m_window = DefaultRootWindow(m_display);
      inactivate_input();
      update();
      set_block_state(false);
    }

    ~InputManager ()
    {
      set_block_state(true);
    }

    void flush_stdin_until (const int end)
    {
      do
      {
        int c = fgetc(stdin);
        if (c == end)
        {
          break;
        }
      } while (true);
    }

    void update ()
    {
      Window tmpWindow;
      int tmpInt;
      XQueryKeymap(m_display, m_keyboard);
      XQueryPointer(m_display, m_window, &tmpWindow, &tmpWindow, &m_mouseXPos, &m_mouseYPos, &tmpInt, &tmpInt, &m_mouseButtonMask);
      XGetWindowAttributes(m_display, m_window, &m_windowAttributes);
      for (int i = 0; i < 256; ++i)
      {
        update_input_status(m_keyboardStatus[i], m_keyboard[static_cast<int>(i / 8)] & (1 << i % 8));
      }
      update_input_status(m_leftMouseButtonStatus, m_mouseButtonMask & 256);
      update_input_status(m_middleMouseButtonStatus, m_mouseButtonMask & 512);
      update_input_status(m_rightMouseButtonStatus, m_mouseButtonMask & 1024);
      return;
    }

    INPUT_STATUS get_key_status (const int key) const
    {
      int code = XKeysymToKeycode(m_display, key);
      return m_keyboardStatus[code];
    }

    bool get_key_state (const int key) const
    {
      int code = XKeysymToKeycode(m_display, key);
      return m_keyboard[static_cast<int>(code / 8)] & (1 << code % 8);
    }

    bool get_mouse_left_button () const
    {
      return (m_mouseButtonMask & 256); 
    }

    bool get_mouse_right_button () const
    {
      return (m_mouseButtonMask & 1024);
    }

    bool get_mouse_middle_button () const
    {
      return (m_mouseButtonMask & 512);
    }

    INPUT_STATUS get_mouse_left_button_status () const
    {
      return m_leftMouseButtonStatus;
    }

    INPUT_STATUS get_mouse_middle_button_status () const
    {
      return m_middleMouseButtonStatus;
    }

    INPUT_STATUS get_mouse_right_button_status () const
    {
      return m_rightMouseButtonStatus;
    }
    
    int get_mouse_x_pos () const
    {
      return m_mouseXPos;
    }

    int get_mouse_y_pos () const
    {
      return m_mouseYPos;
    }

    XWindowAttributes get_window_attributes () const
    {
      return m_windowAttributes;
    }
};

#endif
