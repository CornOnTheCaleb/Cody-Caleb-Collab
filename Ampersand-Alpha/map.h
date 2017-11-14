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
  const double GRAVITY = 19.6;
  // STRINGS:
  const string AIR = term::foreground_color(32, 79, 155) + " " + term::RESET;
  const string CLOUD = term::foreground_color(255, 255, 255) + " " + term::RESET;
  const string BLOCK = "▓";
  const string GRASS = term::foreground_color(22, 63, 6) + "▓" + term::RESET;
  const string WALL = "║";
  const string CEILING = "═";
  const string lCEILING_CORNER = "╔";
  const string rCEILING_CORNER = "╗";
  const string lFLOOR_CORNER = "╚";
  const string rFLOOR_CORNER = "╝";


class World
{
public:
// MEMBER VARIABLES:
  string** map;
  unsigned int WORLD_LENGTH, WORLD_WIDTH;
  
  World(); // Default Constructor

  World(const string map_file); // Parameterized Constructor

  World(const World & rhs); // Copy Constructor

  ~World(); // Destructor

  void insert(const unsigned int x_coord, const unsigned int y_coord, const string character);

  void remove(const unsigned int x_coord, const unsigned int y_coord, const string character = " ");

  void print();

  void clear();

};

#include "map.hpp"
#endif
