#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/input.h>
#include <fstream>
#include <thread>
using namespace std;

class KeyboardManager
{
  private:
    const char * m_keyboardDevice;
    bool m_keyboardState[512];
    ifstream m_deviceStream;
    thread m_thread;
    bool m_threadRunning;
    bool m_terminate;
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

    void update_keyboard_state ()
    {
      m_deviceStream.open(m_keyboardDevice, ifstream::binary);
      if (m_deviceStream.good())
      {
        char buffer[sizeof(input_event)];
        input_event event;
        while (!m_terminate)
        {
          m_deviceStream.read(buffer, sizeof(input_event));
          unsigned char * ptr = (unsigned char *)((void*)&event);
          for (int index = 0; index < sizeof(input_event); ++index)
          {
            *ptr = buffer[index];
            ++ptr;
          }
          m_keyboardState[event.code] = event.value;
          cout << event.code << " " << event.value << endl;
        }
        m_deviceStream.close();
      }
      else
      {
        // RIP
      }
      return;
    }

  public:
    KeyboardManager (const char * device) : m_keyboardDevice(device), m_threadRunning(false), m_terminate(false)
    {
      for (int index = 0; index < 512; ++index)
      {
        m_keyboardState[index] = false;
      }
      set_block_state(false);
    }
    
    ~KeyboardManager ()
    {
      if (m_deviceStream.is_open())
      {
        m_deviceStream.close();
      }
      set_block_state(true);
    }

    void init ()
    {
      if (m_threadRunning == false)
      {
        m_terminate = false;
        m_thread = thread(&KeyboardManager::update_keyboard_state, ref(*this));
        m_threadRunning = true;
      }
      return;
    }
    
    void terminate (const int terminationCode)
    {
      if (m_threadRunning == true)
      {
        m_terminate = true;
        m_thread.join();
        m_threadRunning = false;
        do
        {
          int c = fgetc(stdin);
          if (c == terminationCode)
          {
            break;
          }
        } while (true);
      }
      return;
    }

    bool get_key_state (const int keycode)
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
};

#endif
