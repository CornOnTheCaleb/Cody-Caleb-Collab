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
  char* symbol;
  char* covered;
  bool life;
  unsigned int x_coord, unsigned int y_coord;
  int y_velocity, x_velocity, acceleration;
  int x_terminal_velocity;

public:

// DEFAULT CONSTRUCTOR
  Character()
    {symbol = term::symbol + "&" + term::RESET; x_coord = 0; y_coord = 0;}

// PARAMETERIZED CONSTRUCTOR
  Character(char* const symbol, const unsigned int x, const unsigned int y)
    {symbol = symbol; x_coord = x; y_coord = y;}

// DESTRUCTOR
  ~Character()
  {
    symbol = " ";
    cout << "\e[" << y_coord << ";" << x_coord << << symbol << "H";
    life = false;
  }

// UPDATE
  void update(World map)
  {
    if(map[y

// MOVE
  void move(const char input, World map)
  {
    if(input == 'w')
      jump(map);
    else if(input == 'a')
      strafe(input, map);
    else if(input == 'd')
      strafe(input, map);
  }

// STRAFE
  void strafe(const char input, World map)
  {
    if(input == 'a' && map[y_coord][x_coord - 1] != " ")
      --x_coord;
    else if(input == 'd' && map[y_coord][x_coord + 1] != " ")
      ++x_coord;
  }

// JUMP
  void jump(World map)
  {
    if(y_coord == 54 && map[y_coord + 1][x] == " ")
      y_velocity += 5;    
  }

    
#endif
