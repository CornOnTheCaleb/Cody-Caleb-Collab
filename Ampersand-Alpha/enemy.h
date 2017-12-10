#ifndef ENEMY_H
#define ENEMY_H


#include "map.h"
#include "character.h"

/*
=============================================
--------------------ENEMY--------------------
============================================= */
class Enemy : public Character
{
public:
// PARAMETERIZED CONSTRUCTOR:
  Enemy(const string character, const string back, const double x, const double y, const int vroom)
  {
    background = back;
    symbol = character;
    x_coord = x;
    y_coord = y;
    speed = vroom;
    x_velocity = 0;
    y_velocity = 0;
    covered = AIR;
  }

// MEMBER FUNCTIONS:
  void move(World& map, TimeManager time, Character hero)
  {
    int hero_x = hero.get_x_coord();
    int hero_y = hero.get_y_coord();

    if((int)x_coord == hero_x && (int)y_coord > hero_y)
      jump(map, time);
    else if((int)x_coord < hero_x && is_solid(map.map[(int)y_coord][(int)x_coord + 1]) && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]))
      jump(map, time);
    else if((int)x_coord > hero_x && is_solid(map.map[(int)y_coord][(int)x_coord - 1]) && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]))
      jump(map, time);
    else if((int)x_coord < hero_x)
      strafe('d', map, time);
    else if((int)x_coord > hero_x)
      strafe('a', map, time);
  }
};

#endif
