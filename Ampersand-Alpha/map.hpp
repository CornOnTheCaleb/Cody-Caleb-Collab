#ifndef MAP_HPP
#define MAP_HPP

/*
===========================================================
--------------------DEFAULT CONSTRUCTOR--------------------
=========================================================== */
World::World()
{
  WORLD_LENGTH = TERMINAL_LENGTH;
  WORLD_WIDTH = TERMINAL_WIDTH;

  // creates 2D array for map
  map = new char**[TERMINAL_LENGTH + 1];
  for(int i = 0; i <= TERMINAL_LENGTH; i++)
    map[i] = new char*[TERMINAL_WIDTH + 1];
  // creates green grass block  
  string grass = BLOCK;

  for(int x = 1; x <= TERMINAL_WIDTH; x++)
  {
    for(int y = 1; y <= TERMINAL_LENGTH; y++)
    {
      if(x == 1 && y == 1)
        map[y][x] = const_cast<char*>(lCEILING_CORNER);
      else if(x == 1 && y == TERMINAL_LENGTH)
        map[y][x] = const_cast<char*>(grass.c_str());
      else if(x == TERMINAL_WIDTH && y == 1)
        map[y][x] = const_cast<char*>(rCEILING_CORNER);
      else if(x == TERMINAL_WIDTH && y == TERMINAL_LENGTH)
        map[y][x] = const_cast<char*>(grass.c_str());
      else if(x == 1 || x == TERMINAL_WIDTH)
        map[y][x] = const_cast<char*>(WALL);
      else if(y == 1)
        map[y][x] = const_cast<char*>(CEILING);
      else if(y == TERMINAL_LENGTH)
        map[y][x] = const_cast<char*>(grass.c_str());
      else
        map[y][x] = " ";
    }
  }
}

/*
=================================================================
--------------------PARAMETERIZED CONSTRUCTOR--------------------
================================================================= */
World::World(string map_file)
{
  unsigned int length, width;
  char* tmp;
  ifstream fin;

  fin.open(map_file.c_str());

  fin >> length >> width;
  WORLD_LENGTH = length;
  WORLD_WIDTH = width;

  map = new char**[length + 1];
  for(int i = 0; i <= length; i++)
    map[i] = new char*[width + 1];

  for(int y = 1; y <= length; y++)
  {
    for(int x = 1; x <= width; x++)
    {
      fin >> tmp;
      map[y][x] = tmp;
    }
  }
}

/*
========================================================
--------------------COPY CONSTRUCTOR--------------------
======================================================== */
World::World(const World & rhs)
{
  map = new char**[rhs.WORLD_LENGTH];
  for(int i = 0; i <= rhs.WORLD_LENGTH; i++)
    map[i] = new char*[rhs.WORLD_WIDTH];
  WORLD_LENGTH = rhs.WORLD_LENGTH;
  WORLD_WIDTH = rhs.WORLD_WIDTH;
  for(int y = 0; y <= WORLD_LENGTH; y++)
  {
    for(int x = 0; x <= WORLD_WIDTH; x++)
    {
      map[y][x] = rhs.map[y][x];
    }
  }
}

/*
==================================================
--------------------DESTRUCTOR--------------------
================================================== */
World::~World()
{
  clear();
}

/*
==============================================
--------------------INSERT--------------------
============================================== */
void World::insert(const unsigned int x_coord, const unsigned int y_coord, char const * character)
{
  map[y_coord][x_coord] = const_cast<char*>(character);
}

/*
==============================================
--------------------REMOVE--------------------
============================================== */
void World::remove(const unsigned int x_coord, const unsigned int y_coord, char const * character)
{
  map[y_coord][x_coord] = const_cast<char*>(character);
}

/*
=============================================
--------------------PRINT--------------------
============================================= */
void World::print()
{
  for(int y = 1; y <= WORLD_LENGTH; y++)
  {
    for(int x = 1; x <= WORLD_WIDTH; x++)
    {
      cout << map[y][x];
      if(x == WORLD_WIDTH)
        cout << endl;
    }
  }
}

/*
=============================================
--------------------CLEAR--------------------
============================================= */
void World::clear()
{
  for(int y = WORLD_LENGTH; y >= 0; y--)
    delete[] map[y];
  delete[] map;
}

#endif
