#ifndef TERMINAL_MANAGER_H
#define TERMINAL_MANAGER_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

namespace term
{
  const string BLACK = "\e[0;30m";
  const string RED = "\e[0;31m";
  const string GREEN = "\e[0;32m";
  const string BROWN = "\e[0;33m";
  const string BLUE = "\e[0;34m";
  const string PURPLE = "\e[0;35m";
  const string CYAN = "\e[0;36m";
  const string LIGHT_GRAY = "\e[0;37m";
  const string DARY_GRAY = "\e[1;30m";
  const string LIGHT_RED = "\e[1;31m";
  const string LIGHT_GREEN = "\e[1;32m";
  const string YELLOW = "\e[1;33m";
  const string LIGHT_BLUE = "\e[1;34m";
  const string LIGHT_PURPLE = "\e[1;35m";
  const string LIGHT_CYAN = "\e[1;36m";
  const string WHITE = "\e[1;37m";

  const string CLEAR = "\e[2J";
  const string CLEAR_LINE = "\e[K";
  
  const string RESET = "\e[0m";

  string cursor_move_up (const int lines)
  {
    return ("\e[" + to_string(lines) + "A");
  }

  string cursor_move_down (const int lines)
  {
    return ("\e[" + to_string(lines) + "B");
  }

  string cursor_move_right (const int columns)
  {
    return ("\e[" + to_string(columns) + "C");
  }

  string cursor_move_left (const int columns)
  {
    return ("\e[" + to_string(columns) + "D");
  }

  string cursor_move_to (const int line, const int column)
  {
    return ("\e[" + to_string(line) + ";" + to_string(column) + "H");
  }

  string cursor_hide ()
  {
    return ("\e[?25l");
  }

  string cursor_show ()
  {
    return ("\e[?25h");
  }

  bool supports_true_color ()
  {
    return (string(getenv("COLORTERM")) == "truecolor");
  }

  string foreground_color (const unsigned char red, const unsigned char green, const unsigned char blue)
  {
    return ("\e[38;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m");
  }

  string background_color (const unsigned char red, const unsigned char green, const unsigned char blue)
  {
    return ("\e[48;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m"); 
  }

  void get_dimensions (int & columns, int & lines)
  {
    winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    columns = size.ws_col;
    lines = size.ws_row;
    return;
  }
};

#endif
