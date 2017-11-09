#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <chrono>

using namespace std::chrono;

class TimeManager
{
  private:
    time_point<high_resolution_clock> m_start, m_previous, m_current;
  public:
    TimeManager () : m_start(high_resolution_clock::now()), m_previous(m_start), m_current(m_start) {}
    void update ()
    {
      m_previous = m_current;
      m_current = high_resolution_clock::now();
    }
    double get_delta_time () const
    {
      duration<double> duration = m_current - m_previous;
      return duration.count();
    }
    double get_runtime ()
    {
      update();
      duration<double> duration = m_current - m_start;
      return duration.count();
    }
};

#endif

