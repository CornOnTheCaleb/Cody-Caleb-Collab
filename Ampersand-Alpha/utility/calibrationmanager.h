#ifndef CALIBRATION_MANAGER_H
#define CALIBRATION_MANAGER_H

#include <iostream>
#include <vector>
#include "terminalmanager.h"
#include "inputmanager.h"
#include "timemanager.h"
#include "printmanager.h"

using namespace std;

class CalibrationManager
{
  private:
    struct CalibrationPoint {
      int termX;
      int termY;
      double mouseX;
      double mouseY;
      CalibrationPoint (int x, int y) : termX(x), termY(y), mouseX(0), mouseY(0) {}
    };
  private:
    bool m_calibrated;
    double m_left, m_right, m_top, m_bottom;
  public:
    CalibrationManager () : m_calibrated(false)
    {

    }

    void calibrate (InputManager & input, const int trials = 1)
    {
      int terminalWidth, terminalHeight;
      term::get_dimensions(terminalWidth, terminalHeight);
      
      vector<CalibrationPoint> points = {CalibrationPoint(1, 1), CalibrationPoint(1, terminalHeight), CalibrationPoint(terminalWidth, 1), CalibrationPoint(terminalWidth, terminalHeight)};

      cout << term::cursor_move_to(1, 1) << term::CLEAR << flush;

      bool end = false;
      for (int trial = 0; trial < trials && !end; ++trial)
      {
        for (int i = 0; i < points.size() && !end; ++i)
        {
          bool done = false;
          cout << term::cursor_move_to(points[i].termY, points[i].termX) << term::background_color(0, 255, 0) << "I" << term::RESET << flush;
          while (!done && !end)
          {
            input.update();
            term::get_dimensions(terminalWidth, terminalHeight);
            points[1].termY = terminalHeight;
            points[2].termX = terminalWidth;
            points[3].termX = terminalWidth;
            points[3].termY = terminalHeight;
            if (input.get_key_state(XK_Escape))
            {
              end = true;
              done = true;
            }
            if (input.get_mouse_left_button())
            {
              points[i].mouseX += input.get_mouse_x_pos();
              points[i].mouseY += input.get_mouse_y_pos();
              done = true;
              while (input.get_mouse_left_button()) {
                input.update();
              }
            }
          }
          cout << term::cursor_move_to(1, 1) << term::CLEAR << flush;
        }
      }
      for (int i = 0; i < points.size(); ++i)
      {
        points[i].mouseX /= trials;
        points[i].mouseY /= trials;
      }

      m_top = (points[0].mouseY + points[2].mouseY) / 2;
      m_bottom = (points[1].mouseY + points[3].mouseY) / 2;
      m_left = (points[0].mouseX + points[1].mouseX) / 2;
      m_right = (points[2].mouseX + points[3].mouseX) / 2;
      
      if (!end)
      {
        m_calibrated = true;
      }
    }

    int convert_x (const int mouseX)
    {
      if (m_calibrated)
      {
        int terminalWidth, terminalHeight;
        term::get_dimensions(terminalWidth, terminalHeight);
        return ((terminalWidth / (m_right - m_left)) * (mouseX - m_left) + 1);
      }
      return 0;
    }
    
    int convert_y (const int mouseY)
    {
      if (m_calibrated)
      {
        int terminalWidth, terminalHeight;
        term::get_dimensions(terminalWidth, terminalHeight);
        return ((terminalHeight / (m_bottom - m_top)) * (mouseY - m_top) + 1);
      }
      return 0;
    }
};

#endif
