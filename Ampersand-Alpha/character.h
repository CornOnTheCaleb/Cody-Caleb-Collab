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
  string symbol;
  bool life, jumped;
  double x_coord, y_coord, x_coord_prev, y_coord_prev;
  double y_velocity, x_velocity, x_acceleration, x_terminal_velocity;

public:

// DEFAULT CONSTRUCTOR
  Character()
  {
    symbol = "\e[1;37;46m&" + term::RESET;
    x_coord = 2;
    y_coord = TERMINAL_LENGTH - 1;
    x_velocity = 10;
    y_velocity = 0;
    jumped = false;
  }

// PARAMETERIZED CONSTRUCTOR
  Character(const string character, const double x, const double y)
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
    if(map.map[(int)y_coord + 1][(int)x_coord] == AIR)
      y_velocity += GRAVITY * time.get_delta_time();

    // Y POSITION
    y_coord_prev = y_coord;
    y_coord += y_velocity * time.get_delta_time();
    y_coord = ((int)y_coord > TERMINAL_LENGTH - 1 ? TERMINAL_LENGTH - 1 : y_coord); 
   
    cout << term::cursor_move_to(59, 1) << term::CLEAR_LINE << "DELTATIME: " << time.get_delta_time() << endl;
    cout << term::cursor_move_to(60, 1) << term::CLEAR_LINE << "XCOORD: " << (int)x_coord << " " << x_coord << endl;
    cout << term::cursor_move_to(61, 1) << term::CLEAR_LINE << "PREV: " << (int)x_coord_prev << " " << x_coord_prev << endl;
    cout << term::cursor_move_to(62, 1) << term::CLEAR_LINE << "YCOORD: " << (int)y_coord << " " << y_coord << endl;
    cout << term::cursor_move_to(63, 1) << term::CLEAR_LINE << "PREV: " << (int)y_coord_prev << " " << y_coord_prev << endl;
    cout << term::cursor_move_to(64 ,1) << term::CLEAR_LINE << "BELOW: " << map.map[(int)y_coord + 1][(int)x_coord] << " " << (map.map[(int)y_coord + 1][(int)x_coord] == AIR ? "AIR" : "NOT AIR") << endl;
    cout << term::cursor_move_to(65, 1) << term::CLEAR_LINE << "JUMPED: ";
    if(map.map[(int)y_coord + 1][(int)x_coord] != AIR)
    {
      y_velocity = 0;
      jumped = false;
      // y_coord = TERMINAL_LENGTH - 1;
      cout << "FALSE" << endl;
    }
    else
    {
      jumped = true;
      cout << "TRUE" << endl;
    }
    cout << "\e[" << (int)y_coord << ";" << (int)x_coord << "H" << symbol;
    if(!((int)y_coord == (int)y_coord_prev && (int)x_coord == (int)x_coord_prev)) 
      cout << "\e[" << (int)y_coord_prev << ";" << (int)x_coord_prev << "H" << map.map[(int)y_coord_prev][(int)x_coord_prev];
    cout << flush;
  }

// MOVE
  void move(const char input, World map, TimeManager time)
  {
    if(input == 'w' && map.map[(int)y_coord + 1][(int)x_coord] != AIR)
      jump(map, time);
    else if(input == 'a' || input == 'd')
      strafe(input, map, time);
  }

// STRAFE
  void strafe(const char input, World map, TimeManager time)
  {
    if(input == 'a' && map.map[(int)y_coord][(int)x_coord - 1] == AIR)
    {
      x_coord_prev = x_coord;
      x_coord -= x_velocity * time.get_delta_time();
    }
    else if(input == 'd' && map.map[(int)y_coord][(int)x_coord + 1] == AIR)
    {
      x_coord_prev = x_coord;
      x_coord += x_velocity * time.get_delta_time();
    }
  }

// JUMP
  void jump(World map, TimeManager time)
  {
    if(map.map[(int)y_coord + 1][(int)x_coord] != AIR && map.map[(int)y_coord - 1][(int)x_coord] == AIR && jumped == false)
    {
      y_velocity -= 10;
      jumped = true;
    }
  }
};
    
#endif
