#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

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

class MouseManager
{
  private:
    const char * m_mouseDevice;
    int m_leftButton;
    int m_middleButton;
    int m_rightButton;
    int m_relativeMoveX;
    int m_relativeMoveY;
    ifstream m_deviceStream;
    thread m_thread;
    bool m_threadRunning;
    bool m_terminate;
  private:
    void update_mouse_state ()
    {
      m_deviceStream.open(m_mouseDevice, ifstream::binary);
      if (m_deviceStream.good())
      {
        char buffer[3];
        while (!m_terminate)
        {
          m_deviceStream.read(buffer, 3);
          m_leftButton = buffer[0] & 0x1;
          m_rightButton = buffer[0] & 0x2;
          m_middleButton = data[0] & 0x4;
          m_relativeMoveX = data[1];
          m_relativeMoveY = data[2];
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
    MouseManager (const char * device) : m_mouseDevice(device), m_leftButton(0), m_middleButton(0), m_rightButton(0), m_relativeMoveX(0), m_relativeMoveY(0), m_threadRunning(false), m_terminate(false)
    {
    
    }
    
    ~MouseManager ()
    {
      if (m_deviceStream.is_open())
      {
        m_deviceStream.close();
      }
    }

    void init ()
    {
      if (m_threadRunning == false)
      {
        m_terminate = false;
        m_thread = thread(&MouseManager::update_mouse_state, ref(*this));
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
      }
      return;
    }

    bool get_left_button () const
    {
      return m_leftButton;
    }

    bool get_middle_button () const
    {
      return m_middleButton;
    }

    bool get_right_button () const
    {
      return m_rightButton;
    }

    int get_relative_move_x () const
    {
      return m_relativeMoveX;
    }

    int get_relative_move_y () const
    {
      return m_relativeMoveY;
    }
};

#endif
