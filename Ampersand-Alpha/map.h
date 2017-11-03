#ifndef MAP_H
#define MAP_H

#include "utility/bash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// GLOBAL VARIABLES
  const unsigned int TERMINAL_LENGTH = 54, TERMINAL_WIDTH = 211;
  const unsigned int WORLD_LENGTH = 55, WORLD_WIDTH = 1000;
  const unsigned int MAX_CHARACTER_HEIGHT = 2, MIN_CHARACTER_HEIGHT = 54;
  const int GRAVITY = -9.8;

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

// MEMBER VARIABLES:
  char *** g_map;

public:
  
  World(); // Default Constructor

  World(string map_file); // Parameterized Constructor

  World(const World & rhs); // Copy Constructor

  ~World(); // Destructor

  void insert(const unsigned int x, const unsigned int y, const char * character);

  void remove(const unsigned int x, const unsigned int y, const char * character = " ");

  void print();

  void clear();

};

#endif MAP_H
