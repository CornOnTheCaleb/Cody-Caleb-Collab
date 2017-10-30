#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>

class World
{
// CONSTANT VARIABLES:
  static const char * const BLOCK = "▓";
  static const char * const WALL = "║";
  static const char * const CEILING = "═";
  static const char * const CEILING_CORNER = "╔═";
  static const char * const FLOOR_CORNER = "╚";
  const unsigned int TERMIANL_LENGTH = 55, TERMINAL_WIDTH = 211;
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
