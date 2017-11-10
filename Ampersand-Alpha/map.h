#ifndef MAP_H
#define MAP_H

#include "utility/terminalmanager.h"
#include "utility/timemanager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// GLOBAL VARIABLES
  // INTEGERS:
  const unsigned int TERMINAL_LENGTH = 55, TERMINAL_WIDTH = 211;
  const unsigned int MAX_CHARACTER_HEIGHT = 2, MIN_CHARACTER_HEIGHT = 54;
  const double GRAVITY = -9.8;
  // STRINGS:
  char const * BLOCK = "▓";
  char const * WALL = "║";
  char const * CEILING = "═";
  char const * lCEILING_CORNER = "╔";
  char const * rCEILING_CORNER = "╗";
  char const * lFLOOR_CORNER = "╚";
  char const * rFLOOR_CORNER = "╝";


class World
{
public:
// MEMBER VARIABLES:
  char*** map;
  unsigned int WORLD_LENGTH, WORLD_WIDTH;
  
  World(); // Default Constructor

  World(const string map_file); // Parameterized Constructor

  World(const World & rhs); // Copy Constructor

  ~World(); // Destructor

  void insert(const unsigned int x_coord, const unsigned int y_coord, char const * character);

  void remove(const unsigned int x_coord, const unsigned int y_coord, char const * character = " ");

  void print();

  void clear();

};

#include "map.hpp"
#endif
