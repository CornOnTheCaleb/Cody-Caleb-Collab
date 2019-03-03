#ifndef ENVIRONMENT_CPP
#define ENVIRONMENT_CPP
#include "environment.hpp"

/*
-----------------------------------------------------------------
                    PARAMETERIZED CONSTRUCTOR
----------------------------------------------------------------- */
// add actor input
Environment::Environment( const int length, const int width )
{
  std::ifstream fin;
  // if( !fin.is_open() ) throw Error;
  // if( fin.eof() ) throw Error;
  // resize each vector in grid
  grid.resize(width);
  for(int i = 0; i < width; i++)
    grid[i].resize(length);
  for(int x = 0; x < width; x++)
  {
    for(int y = 0; y < length; y++)
      grid[x][y].push_back(BLOCK);
  }
} /* parameterized constructor */

/*
-----------------------------------------------------------------
                    PARAMETERIZED CONSTRUCTOR
----------------------------------------------------------------- */
// add actor input
Environment::Environment( const string file_name )
{
  std::ifstream fin;
  int length = 0,
      width = 0;
  // if( !fin.is_open() ) throw Error;
  // if( fin.eof() ) throw Error;
  fin >> length >> width;
  // resize each vector in grid
  grid.resize(width);
  for(int i = 0; i < width; i++)
    grid[i].resize(length);
  for(int x = 0; x < width; x++)
  {
    for(int y = 0; y < length; y++)
      grid[x][y].push_back(BLOCK);
  }
} /* parameterized constructor */

/*
-------------------------------------------------
                    GET WIDTH
------------------------------------------------- */
int Environment::get_width() const
{
  return grid.size();
}

/*
--------------------------------------------------
                    GET LENGTH
-------------------------------------------------- */
int Environment::get_length() const
{
  return grid[0].size();
}

/*
--------------------------------------------------
                    GET HEIGHT
-------------------------------------------------- */
int Environment::get_height() const
{
  return grid[0][0].size();
}

/*
--------------------------------------------
                    PRINT
-------------------------------------------- */
void Environment::print() const
{
  for(int y = 0; y < get_length(); y++)
  {
    for(int x = 0; x < get_width(); x++)
    {
      std::cout << grid[x][y][0];
    }
    std::cout << std::endl;
  }
}

int main()
{
  Environment environment(10, 10);
  environment.print();
  return 0;
}

#endif