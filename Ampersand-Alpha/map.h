#ifndef MAP_H
#define MAP_H

#include "utility/bash.h"
#include "utility/timemanager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// GLOBAL VARIABLES
  const unsigned int TERMINAL_LENGTH = 55, TERMINAL_WIDTH = 211;
  const unsigned int MAX_CHARACTER_HEIGHT = 2, MIN_CHARACTER_HEIGHT = 54;
  const double GRAVITY = -9.8;

class World
{
// CONSTANT VARIABLES:
  static char * const BLOCK = "▓";
  static char * const WALL = "║";
  static char * const CEILING = "═";
  static char * const lCEILING_CORNER = "╔";
  static char * const rCEILING_CORNER = "╗";
  static char * const lFLOOR_CORNER = "╚";
  static char * const rFLOOR_CORNER = "╝";

public:
// MEMBER VARIABLES:
  char*** map;
  unsigned int WORLD_LENGTH, WORLD_WIDTH;
  
  World(); // Default Constructor

  World(const string map_file); // Parameterized Constructor

  World(const World & rhs); // Copy Constructor

  ~World(); // Destructor

  void insert(const unsigned int x_coord, const unsigned int y_coord, const char * character);

  void remove(const unsigned int x_coord, const unsigned int y_coord, const char * character = " ");

  void print();

  void clear();

};

#include "map.hpp"
#endif MAP_H
