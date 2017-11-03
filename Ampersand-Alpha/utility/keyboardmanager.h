#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <stropts.h>
#include <fcntl.h>
#include <linux/input.h>

using namespace std;

class KeyboardManager
{
  private:
    char * m_keyboardDevice;
    int m_keyboardState[512];
  public:
    enum STATE
    {
      RELEASED,
      PRESSED,
      HELD,
      INACTIVE,
    };
  private:
    void set_block_state (const bool state)
    {
      termios ttystate;
      tcgetattr(STDIN_FILENO, &ttystate);
      if (state == false)
      {
        ttystate.c_lflag &= (~ICANON & ~ECHO); //Not display character
        ttystate.c_cc[VMIN] = 1;
      }
      else if (state == true)
      {
        ttystate.c_lflag |= ICANON | ECHO;
      }
      tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
      return;
    }

    int khbit ()
    {
      timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
      return FD_ISSET(STDIN_FILENO, &fds);
    }
  public:
    KeyboardManager ()
    {
      set_block_state(false);
    }
    
    ~KeyboardManager ()
    {
      set_block_state(true);
    }
    
    void update_keyboard_state ()
    {
      int kbd = open(m_keyboardDevice, O_RDONLY);
      if (kbd != -1)
      {
        input_event ie;
        while (read(kbd, &ie, sizeof(ie)))
        {
          m_keyboardState[ie.code] = ie.value;
        }
        close(kbd);
      }
    }

    int get_keyboard_state (const int keycode)
    {
      return m_keyboardState[keycode];
    }

    char getch ()
    {
      if (khbit() != 0)
      {
        char c = fgetc(stdin);
        return c;
      }
      return '\0';
    }
}

#endif
