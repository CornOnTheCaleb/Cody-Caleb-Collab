#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <iostream>

using namespace std;

/*
  EXAMPLE USAGE:

  nonblock(true);
  while (true)
  {
    char c;
    if (c = getch())
    {
      dostuff(c);
      if (c == 27) // ESC
      {
        break;
      }
    }
  }
  nonblock(false);
*/

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

void nonblock (const bool state)
{
  termios ttystate;
  tcgetattr(STDIN_FILENO, &ttystate);
  if (state == true)
  {
    ttystate.c_lflag &= (~ICANON & ~ECHO); //Not display character
    ttystate.c_cc[VMIN] = 1;
  }
  else if (state == false)
  {
    ttystate.c_lflag |= ICANON | ECHO;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
  return;
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

#endif
