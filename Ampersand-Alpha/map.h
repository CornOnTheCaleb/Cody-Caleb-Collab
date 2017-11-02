#ifndef MAP_H
#define MAP_H

#include "utility/bash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
  const unsigned int TERMIANL_LENGTH = 54, TERMINAL_WIDTH = 211;
  const unsigned int WORLD_LENGTH = 55, WORLD_WIDTH = 1000;

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
