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
  bool life;
  unsigned int x_coord, y_coord;
  unsigned int x_cood_prev, y_coord_prev;
  int y_velocity, x_velocity, acceleration;
  int x_terminal_velocity;

public:

// DEFAULT CONSTRUCTOR
  Character()
    {symbol = term::CYAN + "&" + term::RESET; x_coord = 0; y_coord = 0;}

// PARAMETERIZED CONSTRUCTOR
  Character(char* const character, const unsigned int x, const unsigned int y)
    {symbol = character; x_coord = x; y_coord = y;}

// DESTRUCTOR
  ~Character()
  {
    symbol = " ";
    cout << "\e[" << y_coord << ";" << x_coord << symbol << "H";
    life = false;
  }

// UPDATE
  void update_character(World map, TimeManager time)
  {
    // Y VELOCITY
    if(map.map[y_coord + 1][x_coord] == " " && y_velocity != 0)
      y_velocity += GRAVITY * time.get_delta_time();
    else
    {
      y_velocity = 0;
      y_velocity += GRAVITY * time.get_delta_time();
    }
    // Y POSITION
    y_coord_prev = y_coord;
    y_coord += y_velocity * time.get_delta_time();
    cout << "\e[" << y_coord << ";" << x_coord << map.map[y_coord_prev][x_coord_prev] << "H";
  }

      

// MOVE
  void move(const char input, World map)
  {
    if(input == 'w')
      jump(map);
    else if(input == 'a' || input == 'd')
      strafe(input, map);
  }

// STRAFE
  void strafe(const char input, World map)
  {
    if(input == 'a' && map[y_coord][x_coord - 1] == " ")
    {
      x_coord_prev = x_coord;
      --x_coord;
    }
    else if(input == 'd' && map[y_coord][x_coord + 1] == " ")
    {
      x_coord_prev = x_coord;
      ++x_coord;
    }
  }

// JUMP
  void jump(World map)
  {
    if(y_coord == 54 && map[y_coord + 1][x] == " ")
      y_velocity += 5;    
  }
};
    
#endif
