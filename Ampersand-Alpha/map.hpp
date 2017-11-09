#ifndef MAP_HPP
#define MAP_HPP

World::World()
{
  map = new char***[TERMINAL_LENGTH + 1];
  for(int i = 0; i <= TERMINAL_LENGTH; i++)
    map[i] = new char**[TERMINAL_WIDTH + 1];
  string grass = BLOCK;
  grass.insert(0, term::GREEN);

  for(int x = 1; x <= TERMINAL_WIDTH; x++)
  {
    for(int y = 1; y <= TERMINAL_LENGTH; y++)
    {
      if(x == 1 && y == 1)
        map[y][x] = lCEILING_CORNER;
      else if(x == 1 && y == TERMINAL_LENGTH)
        map[y][x] = grass;
      else if(x == TERMINAL_WIDTH && y == 1)
        map[y][x] = rCEILING_CORNER;
      else if(x == TERMINAL_WIDTH && y == TERMINAL_LENGTH)
        map[y][x] = grass;
      else if(x == 1 || x == TERMINAL_WIDTH)
        map[y][x] = WALL;
      else if(y == 1)
        map[y][x] = CIELING;
      else if(y == TERMINAL_LENGTH)
        map[y][x] = grass;
      else
        map[y][x] = " ";
    }
  }
}

World::World(string map_file)
{
  unsigned int length, width;
  char* tmp;
  ifstream fin;

  fin.open(map_file.c_str());
  fin >> length >> width;
  map = new char***[length + 1];
  for(int i = 0; i <= length; i++)
    map[i] = new char**[width + 1];

  for(int x = 1; x <= width; x++)
  {
    for(int y = 1; y <= length; y++)
    {
      fin >> tmp;
      map[y][x] = tmp;
    }
  }
}
#endif
