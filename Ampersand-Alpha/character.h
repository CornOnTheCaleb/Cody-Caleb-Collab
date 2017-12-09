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
  string symbol, covered;
  bool life, jumped;
  double x_coord, y_coord, x_coord_prev, y_coord_prev;
  double y_velocity, x_velocity, x_acceleration, x_terminal_velocity;

public:

// DEFAULT CONSTRUCTOR
  Character()
  {
    symbol = term::background_color(32, 79, 155) + "&" + term::RESET;
    x_coord = 2;
    y_coord = TERMINAL_LENGTH - 1;
    x_velocity = 10;
    y_velocity = 0;
    jumped = false;
    covered = AIR;
  }

// PARAMETERIZED CONSTRUCTOR
  Character(const string character, const double x, const double y)
  {
    symbol = character;
    x_coord = x;
    y_coord = y;
    x_velocity = 10;
    y_velocity = 0;
    jumped = false;
    covered = AIR;
  }

// DESTRUCTOR
  ~Character()
  {
    life = false;
  }

// GET X COORDINATE
  int get_x_coord()
    {return (int)x_coord;}

// GET Y COORDINATE
  int get_y_coord()
    {return (int)y_coord;}

// UPDATE
  void update_character(World& map, TimeManager time)
  {
    // covered = map.map[(int)y_coord][(int)x_coord];
    // Y VELOCITY
    if(!is_solid(map.map[(int)y_coord + 1][(int)x_coord]))
      y_velocity += GRAVITY * time.get_delta_time();

    // Y POSITION
    y_coord_prev = y_coord;
    y_coord += y_velocity * time.get_delta_time();
    // bounds character below
    y_coord = ((int)y_coord > TERMINAL_LENGTH - 1 ? TERMINAL_LENGTH - 1 : y_coord);
    // bounds character above
    y_coord = ((int)y_coord < 2 ? 2 : y_coord);

    x_coord_prev = x_coord;
    x_coord = x_coord + x_velocity * time.get_delta_time();
    x_velocity = 0;

    double y = y_coord_prev;
    bool moving = true;
    if (y < y_coord)
    {
      while (moving)
      {
        if (!is_solid(map.map[(int)y + 1][(int)x_coord]) && y < y_coord)
        {
          y += 1;
          if (y > y_coord)
          {
            y = y_coord;
          }
        }
        else
        {
          if (y != y_coord)
          {
            jumped = false;
            y_velocity = 0;
            y = (int)(y + 1) - 0.0001;
          }
          moving = false;
        }
      }
    }
    else if (y > y_coord)
    {
      while (moving)
      {
        if (!is_solid(map.map[(int)y - 1][(int)x_coord]) && y > y_coord)
        {
          y -= 1;
          if (y < y_coord)
          {
            y = y_coord;
          }
        }
        else
        {
          if (y != y_coord)
          {
            y_velocity = 0;
          }
          moving = false;
        }
      }
    }
    y_coord = y;

    /* DEBUG */
    bool DEBUG = true;
    if (DEBUG)
    {
      cout << term::cursor_move_to(56, 1) << "delta time: " << time.get_delta_time() << " seconds" << term::CLEAR_LINE << endl
        << "x_coord: " << x_coord << " (" << (int)x_coord << ")" << term::CLEAR_LINE << endl
        << "x_coord_prev: " << x_coord_prev << " (" << (int)x_coord_prev << ")" << term::CLEAR_LINE << endl
        << "y_coord: " << y_coord << " (" << (int)y_coord << ")" << term::CLEAR_LINE << endl
        << "y_coord_prev: " << y_coord_prev << " (" << (int)y_coord_prev << ")" << term::CLEAR_LINE << endl
        << "previous: " << map.map[(int)y_coord_prev][(int)x_coord_prev] << term::CLEAR_LINE << endl
        << "current: " << map.map[(int)y_coord][(int)x_coord] << term::CLEAR_LINE << endl
        << "symbol: " << symbol << term::CLEAR_LINE << endl
        << "covered: " << covered << term::CLEAR_LINE << endl
        << "below: " << map.map[(int)y_coord + 1][(int)x_coord] << term::CLEAR_LINE << endl
        << "above: " << map.map[(int)y_coord - 1][(int)x_coord] << term::CLEAR_LINE << endl;
    }

    // output character if it moved
    if(!((int)y_coord == (int)y_coord_prev && (int)x_coord == (int)x_coord_prev)) 
    {  
      map.insert((int)x_coord_prev, (int)y_coord_prev, covered);
      covered = map.map[(int)y_coord][(int)x_coord];
      size_t a = covered.find("\e[48;2;");
      size_t b = covered.find("m", a);
      symbol = covered.substr(a, b - a + 1) + "&" + term::RESET;
    }
    map.insert((int)x_coord, (int)y_coord, symbol);
  }

// MOVE
  void move(const char input, World& map, TimeManager time)
  {
    if(input == 'w' && is_solid(map.map[(int)y_coord + 1][(int)x_coord]))
      jump(map, time);
    else if(input == 'a' || input == 'd')
      strafe(input, map, time);
  }

// STRAFE
  void strafe(const char input, World& map, TimeManager time)
  {
    if(input == 'a' && !is_solid(map.map[(int)y_coord][(int)x_coord - 1]))
    {
      x_velocity = -20;
      // x_coord_prev = x_coord;
      // x_coord -= x_velocity * time.get_delta_time();
    }
    else if(input == 'd' && !is_solid(map.map[(int)y_coord][(int)x_coord + 1]))
    {
      x_velocity = 20;
      // x_coord_prev = x_coord;
      // x_coord += x_velocity * time.get_delta_time();
    }
  }

// JUMP
  void jump(World& map, TimeManager time)
  {
    if(is_solid(map.map[(int)y_coord + 1][(int)x_coord]) && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]) && jumped == false)
    {
      y_velocity -= 25;
      jumped = true;
    }
  }
};
    
#endif
