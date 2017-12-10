#ifndef CHARACTER_H
#define CHARACTER_H

#include "map.h"

/*
=================================================
--------------------CHARACTER--------------------
================================================= */
class Character
{
#ifdef DEBUG
public:
#else
protected:
#endif
// VARIABLES:
  string background, symbol, covered;
  bool life, jumped;
  double x_coord, y_coord, x_coord_prev, y_coord_prev;
  double y_velocity, x_velocity, x_acceleration, x_terminal_velocity, speed;

public:

// DEFAULT CONSTRUCTOR
  Character()
  {
    background = term::background_color(32, 79, 155);
    symbol = term::foreground_color(255, 0, 0) + "&" + term::RESET;
    x_coord = 2;
    y_coord = TERMINAL_LENGTH - 1;
    x_velocity = 10;
    y_velocity = 0;
    covered = AIR;
    jumped = false;
  }

// PARAMETERIZED CONSTRUCTOR
  Character(const string character, const string back, const double x, const double y, const int vroom)
  {
    background = back;
    symbol = character;
    x_coord = x;
    y_coord = y;
    speed = vroom;
    x_velocity = 0;
    y_velocity = 0;
    covered = AIR;
    jumped = false;
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

    double x = x_coord_prev;
    bool moving = true;
    if (x < x_coord)
    {
      while (moving)
      {
        if (!is_solid(map.map[(int)y_coord_prev][(int)x + 1]) && x < x_coord)
        {
          x += 1;
          if (x > x_coord)
          {
            x = x_coord;
          }
        }
        else
        {
          if (x != x_coord)
          {
            x_velocity = 0;
            x = (int)(x + 1) - 0.0001;
          }
          moving = false;
        }
      }
    }
    else if (x > x_coord)
    {
      while (moving)
      {
        if (!is_solid(map.map[(int)y_coord_prev][(int)x - 1]) && x > x_coord)
        {
          x -= 1;
          if (x < x_coord)
          {
            x = x_coord;
          }
        }
        else
        {
          if (x != x_coord)
          {
            x_velocity = 0;
          }
          moving = false;
        }
      }
    }
    x_coord = x;

    double y = y_coord_prev;
    moving = true;
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
            y_velocity = 0;
            y = (int)(y + 1) - 0.0001;
            jumped = false;
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
    if (y == y_coord_prev)
    {
      jumped = false;
    }
    y_coord = y;

    // output character if it moved
    if(!((int)y_coord == (int)y_coord_prev && (int)x_coord == (int)x_coord_prev)) 
    {  
      map.insert((int)x_coord_prev, (int)y_coord_prev, covered);
      covered = map.map[(int)y_coord][(int)x_coord];
      size_t a = covered.find("\e[48;2;");
      size_t b = covered.find("m", a);
      background = covered.substr(a, b - a + 1);
    }
    map.insert((int)x_coord, (int)y_coord, background + symbol);
  }

// MOVE
  virtual void move(const char input, World& map, TimeManager time)
  {
    if(input == 'w' && is_solid(map.map[(int)y_coord + 1][(int)x_coord]) && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]))
      jump(map, time);
    else if(input == 'a' || input == 'd')
      strafe(input, map, time);
  }

// STRAFE
  void strafe(const char input, World& map, TimeManager time)
  {
    if(input == 'a' && !is_solid(map.map[(int)y_coord][(int)x_coord - 1]))
      x_velocity = -speed;

    else if(input == 'd' && !is_solid(map.map[(int)y_coord][(int)x_coord + 1]))
      x_velocity = speed;
  }

// JUMP
  void jump(World& map, TimeManager time)
  {
    if(is_solid(map.map[(int)y_coord + 1][(int)x_coord]) && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]) && !jumped)
    {
      y_velocity = -25;
      jumped = true;
    }
  }
};

#endif
