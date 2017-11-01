#ifndef CHARACTER_H
#define CHARACTER_H

#include "map.h"

/*
=================================================
--------------------CHARACTER--------------------
================================================= */
class Character
{
// VARIABLES:
  char* HERO = term::CYAN + "&" + term::RESET;
  char* covered;
  unsigned int x_coord, unsigned int y_coord;

public:

// DEFAULT CONSTRUCTOR
  Character()
    {HERO = term::HERO + "&" + term::RESET; x_coord = 0; y_coord = 0;}

// PARAMETERIZED CONSTRUCTOR
  Character(char* const symbol, const unsigned int x, const unsigned int y)
    {HERO = symbol; x_coord = x; y_coord = y;}

// STRAFE
  void strafe(const char input, World map)
  {
    if(input == 'a' && map[y_coord][x_coord - 1] != " "))
      --x_coord;
    else if(input == 'd' && map[y_coord][x_coord + 1] != " ")
      ++x_coord;
  }
#endif
