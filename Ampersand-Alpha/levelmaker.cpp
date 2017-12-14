#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "utility/terminalmanager.h"
#include "utility/inputmanager.h"
#include "utility/timemanager.h"
#include "utility/printmanager.h"
#include "utility/calibrationmanager.h"
#include "utility/miscellaneous.h"
#include "map.h"

using namespace std;

typedef void (*void_function)(void);

const int DIRECTIONS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int ROTATE_LEFT = -1;
const int ROTATE_RIGHT = 1;
const bool FALSE = false;
const bool TRUE = true;

struct MakerEngine
{
  InputManager inputManager;
  TimeManager timeManager;
  PrintManager printManager;
  CalibrationManager calibrationManager;
  
  World flat;
  vector<World> backupLayers;
  vector<World> layers;
  int selectedLayer;
  vector<string> materials;
  int selectedMaterial;
  int prevSelectedMaterial;
  int terminalWidth, terminalHeight;
  int prevTerminalWidth, prevTerminalHeight;
  int printWorldFromX, printWorldToX, printWorldFromY, printWorldToY;
  bool smartPrint;
  bool terminate;
  int viewportFromX;
  int viewportToX;
  int viewportFromY;
  int viewportToY;

  World clipboard;
  bool shift;

  MakerEngine (World & world) : flat(world), backupLayers({world}), layers({world}), selectedLayer(0), selectedMaterial(0), prevSelectedMaterial(0), terminalWidth(0), terminalHeight(0), prevTerminalWidth(0), prevTerminalHeight(0), printWorldFromX(1), printWorldToX(world.WORLD_WIDTH), printWorldFromY(1), printWorldToY(world.WORLD_LENGTH), smartPrint(false), terminate(false), viewportFromX(0), viewportToX(0), viewportFromY(0), viewportToY(0), clipboard(World(world.WORLD_WIDTH, world.WORLD_LENGTH, "\0")), shift(false)
  {
    materials = {
      AIR, GRASS, VEGETATION, CLOUD, WALL, CEILING, lCEILING_CORNER, rCEILING_CORNER, lFLOOR_CORNER, rFLOOR_CORNER, "\0"
    };
  }
};

void update (MakerEngine & engine);
void print (MakerEngine & engine);

void get_mouse_terminal_coordinates (MakerEngine & engine, int & terminalX, int & terminalY)
{
  terminalX = clamp(engine.calibrationManager.convert_x(engine.inputManager.get_mouse_x_pos()), 1, engine.terminalWidth);
  terminalY = clamp(engine.calibrationManager.convert_y(engine.inputManager.get_mouse_y_pos()), 1, engine.terminalHeight);
}

void get_mouse_world_coordinates (MakerEngine & engine, int & worldX, int & worldY)
{
  get_mouse_terminal_coordinates(engine, worldX, worldY);
  worldX += engine.printWorldFromX - engine.viewportFromX;
  worldY += engine.printWorldFromY - engine.viewportFromY;
  worldX = clamp(worldX, engine.printWorldFromX, engine.printWorldToX);
  worldY = clamp(worldY, engine.printWorldFromY, engine.printWorldToY);
}

void get_prev_mouse_terminal_coordinates (MakerEngine & engine, int & terminalX, int & terminalY)
{
  terminalX = clamp(engine.calibrationManager.convert_x(engine.inputManager.get_prev_mouse_x_pos()), 1, engine.terminalWidth);
  terminalY = clamp(engine.calibrationManager.convert_y(engine.inputManager.get_prev_mouse_y_pos()), 1, engine.terminalHeight);
}

void get_prev_mouse_world_coordinates (MakerEngine & engine, int & worldX, int & worldY)
{
  get_prev_mouse_terminal_coordinates(engine, worldX, worldY);
  worldX += engine.printWorldFromX - engine.viewportFromX;
  worldY += engine.printWorldFromY - engine.viewportFromY;
  worldX = clamp(worldX, engine.printWorldFromX, engine.printWorldToX);
  worldY = clamp(worldY, engine.printWorldFromY, engine.printWorldToY);
}

void undo_draw (MakerEngine & engine, vector<void*> params)
{
  if (engine.layers.size() != engine.backupLayers.size())
  {
    ++engine.selectedLayer;
  }
  vector<World> temp = engine.layers;
  engine.layers = engine.backupLayers;
  engine.backupLayers = temp;
}

void backup (MakerEngine & engine, vector<void*>)
{
  engine.backupLayers = engine.layers;
}

void create_new_layer (MakerEngine & engine, vector<void*> params)
{
  backup(engine, {});
  engine.layers.push_back(World(engine.layers[0].WORLD_WIDTH, engine.layers[0].WORLD_LENGTH, "\0"));
}

void delete_layer (MakerEngine & engine, vector<void*> params)
{
  if (engine.layers.size() > 1)
  {
    backup(engine, {});
    engine.layers.erase(engine.layers.begin() + engine.selectedLayer);
    --engine.selectedLayer;
  }
}

void recursive_flood_fill (World & world, const int x, const int y, const string fromMaterial, const string toMaterial)
{
  if (fromMaterial != toMaterial)
  {
    world.insert(x, y, toMaterial);
    for (int direction = 0; direction < 4; ++direction)
    {
      int newX = x + DIRECTIONS[direction][0];
      int newY = y + DIRECTIONS[direction][1];
      if (newX >= 1 && newX <= world.WORLD_WIDTH && newY >= 1 && newY <= world.WORLD_LENGTH)
      {
        if (world.map[newY][newX] == fromMaterial)
        {
          recursive_flood_fill(world, newX, newY, fromMaterial, toMaterial);
        }
      }
    }
  }
}

void flood_fill (MakerEngine & engine, vector<void*> params)
{
  backup(engine, {});
  int x, y;
  get_mouse_world_coordinates(engine, x, y);
  recursive_flood_fill(engine.layers[engine.selectedLayer], x, y, engine.layers[engine.selectedLayer].map[y][x], engine.materials[engine.selectedMaterial]);
}

void brush_fill (MakerEngine & engine, vector<void*> params)
{
  int x, y;
  get_mouse_world_coordinates(engine, x, y);
  engine.layers[engine.selectedLayer].insert(x, y, engine.materials[engine.selectedMaterial]);
}

void rectangle_fill (MakerEngine & engine, vector<void*> params)
{
  backup(engine, {});
  int x1, y1;
  int x2, y2;
  while (!engine.inputManager.get_mouse_left_button())
  {
    update(engine);
    print(engine);
    get_mouse_world_coordinates(engine, x1, y1);
  }
  while (engine.inputManager.get_mouse_left_button())
  {
    engine.inputManager.update();
  }
  while (!engine.inputManager.get_mouse_left_button())
  {
    update(engine);
    print(engine);
    get_mouse_world_coordinates(engine, x2, y2);
  }
  while (engine.inputManager.get_mouse_left_button())
  {
    engine.inputManager.update();
  }
  int x = x1;
  do
  {
    int y = y1;
    do
    {
      engine.layers[engine.selectedLayer].insert(x, y, engine.materials[engine.selectedMaterial]);
      if (y <= y2 && y1 < y2)
      {
        ++y;
      }
      else if (y >= y2 && y1 > y2)
      {
        --y;
      }
    } while ((y1 < y2 && y <= y2) || (y1 > y2 && y >= y2));
    if (x <= x2 && x1 < x2)
    {
      ++x;
    }
    else if (x >= x2 && x1 > x2)
    {
      --x;
    }
  } while ((x1 < x2 && x <= x2) || (x1 > x2 && x >= x2));
}

void line_fill (MakerEngine & engine, vector<void*> params)
{
  backup(engine, {});
  const double changeX = 1E-4;
  int x1, y1;
  int x2, y2;
  while (!engine.inputManager.get_mouse_left_button())
  {
    update(engine);
    print(engine);
    get_mouse_world_coordinates(engine, x1, y1);
  }
  while (engine.inputManager.get_mouse_left_button())
  {
    engine.inputManager.update();
  }
  while (!engine.inputManager.get_mouse_left_button())
  {
    update(engine);
    print(engine);
    get_mouse_world_coordinates(engine, x2, y2);
  }
  while (engine.inputManager.get_mouse_left_button())
  {
    engine.inputManager.update();
  }
  double m = static_cast<double>(y2 - y1) / (x2 - x1 + 1E-2);
  double b = -m * x1 + y1;
  double x = x1;
  do
  {
    int y = m * x + b;
    engine.layers[engine.selectedLayer].insert((int)x, y, engine.materials[engine.selectedMaterial]);
    if (x <= x2 + changeX && x1 < x2)
    {
      x += changeX;
    }
    else if (x >= x2 && x1 > x2)
    {
      x -= changeX;
    }
  } while ((x1 < x2 && x <= x2 + changeX) || (x1 > x2 && x >= x2));
  engine.layers[engine.selectedLayer].insert(x2, y2, engine.materials[engine.selectedMaterial]);
}

void rotate_material (MakerEngine & engine, vector<void*> params)
{
  engine.prevSelectedMaterial = engine.selectedMaterial;
  engine.selectedMaterial += (*((int*)(params[0])));
  engine.selectedMaterial = (engine.selectedMaterial < 0 ? engine.materials.size() - 1 : engine.selectedMaterial % engine.materials.size());
}

void rotate_layer (MakerEngine & engine, vector<void*> params)
{
  engine.selectedLayer += (*((int*)(params[0])));
  engine.selectedLayer = (engine.selectedLayer < 0 ? engine.layers.size() - 1 : engine.selectedLayer % engine.layers.size());
}

void magic_wand_select (MakerEngine & engine, vector<void*> params)
{
  World temp = engine.layers[engine.selectedLayer];
  if (!engine.shift)
  {
    engine.clipboard = World(temp.WORLD_WIDTH, temp.WORLD_LENGTH, "\0");
  }
  int startX, startY;
  get_mouse_world_coordinates(engine, startX, startY);
  string mat = temp.map[startY][startX];
  recursive_flood_fill(temp, startX, startY, mat, "SELECTED");
  for (int x = 1; x <= temp.WORLD_WIDTH; ++x)
  {
    for (int y = 1; y <= temp.WORLD_LENGTH; ++y)
    {
      if (temp.map[y][x] == "SELECTED")
      {
        engine.clipboard.insert(x, y, mat);
      }
    }
  }
}

void paste (MakerEngine & engine, vector<void*> params)
{
  backup(engine, {});
  int startX, startY;
  get_mouse_world_coordinates(engine, startX, startY);
  unsigned int fromX = -1;
  unsigned int toX = 0;
  unsigned int fromY = -1;
  unsigned int toY = 0;
  for (int x = 1; x <= engine.clipboard.WORLD_WIDTH; ++x)
  {
    for (int y = 1; y <= engine.clipboard.WORLD_LENGTH; ++y)
    {
      if (engine.clipboard.map[y][x] != "\0")
      {
        if (x < fromX)
        {
          fromX = x;
        }
        else if (x > toX)
        {
          toX = x;
        }
        if (y < fromY)
        {
          fromY = y;
        }
        else if (y > toY)
        {
          toY = y;
        }
      }
    }
  }
  for (int x = fromX; x <= toX; ++x)
  {
    for (int y = fromY; y <= toY; ++y)
    {
      string mat = engine.clipboard.map[y][x];
      int a = x - fromX + startX;
      int b = y - fromY + startY;
      if (mat != "\0" && a >= 1 && a <= engine.layers[engine.selectedLayer].WORLD_WIDTH && b >= 1 && b <= engine.layers[engine.selectedLayer].WORLD_LENGTH)
      {
        engine.layers[engine.selectedLayer].insert(a, b, mat);
      }
    }
  }
}

void set_shift (MakerEngine & engine, vector<void*> params)
{
  engine.shift = *((bool*)(params[0]));
}

void update (MakerEngine & engine)
{
  engine.inputManager.update();
  engine.timeManager.update();
  engine.prevTerminalWidth = engine.terminalWidth;
  engine.prevTerminalHeight = engine.terminalHeight;
  term::get_dimensions(engine.terminalWidth, engine.terminalHeight);
  engine.viewportFromX = 2;
  engine.viewportToX = engine.terminalWidth - 1;
  engine.viewportFromY = 2;
  engine.viewportToY = engine.terminalHeight - 2;
  if (engine.terminalWidth != engine.prevTerminalWidth)
  {
    engine.smartPrint = false;
    if ((engine.viewportToX - engine.viewportFromX + 1) >= engine.layers[engine.selectedLayer].WORLD_WIDTH)
    {
      engine.printWorldFromX = 1;
      engine.printWorldToX = engine.layers[engine.selectedLayer].WORLD_WIDTH;
    }
    engine.printWorldToX = engine.printWorldFromX + (engine.viewportToX - engine.viewportFromX + 1) - 1;
    if (engine.printWorldToX > engine.layers[engine.selectedLayer].WORLD_WIDTH)
    {
      engine.printWorldToX = engine.layers[engine.selectedLayer].WORLD_WIDTH;
      if ((engine.printWorldToX - engine.printWorldFromX + 1) < (engine.viewportToX - engine.viewportFromX + 1))
      {
        engine.printWorldFromX = engine.printWorldToX - (engine.viewportToX - engine.viewportFromX + 1) + 1;
        if (engine.printWorldFromX < 1)
        {
          engine.printWorldFromX = 1;
        }
      }
    }
  }
  if (engine.terminalHeight != engine.prevTerminalHeight)
  {
    engine.smartPrint = false;
    if ((engine.viewportToY - engine.viewportFromY + 1) >= engine.layers[engine.selectedLayer].WORLD_LENGTH)
    {
      engine.printWorldFromY = 1;
      engine.printWorldToY = engine.layers[engine.selectedLayer].WORLD_LENGTH;
    }
    engine.printWorldToY = engine.printWorldFromY + (engine.viewportToY - engine.viewportFromY + 1) - 1;
    if (engine.printWorldToY > engine.layers[engine.selectedLayer].WORLD_LENGTH)
    {
      engine.printWorldToY = engine.layers[engine.selectedLayer].WORLD_LENGTH;
      if ((engine.printWorldToY - engine.printWorldFromY + 1) < (engine.viewportToY - engine.viewportFromY + 1))
      {
        engine.printWorldFromY  = engine.printWorldToY - (engine.viewportToY - engine.viewportFromY + 1) + 1;
        if (engine.printWorldFromY < 1)
        {
          engine.printWorldFromY = 1;
        }
      }
    }
  }
}

void shift_viewport (MakerEngine & engine, vector<void*> params)
{
  int shiftX = (*((int*)params[0])) * (engine.viewportToX - engine.viewportFromX + 1) / 8;
  int shiftY = (*((int*)params[1])) * (engine.viewportToY - engine.viewportFromY + 1) / 8;
  if (shiftX < 0 && engine.printWorldFromX - 1 < -shiftX)
  {
    shiftX = -(engine.printWorldFromX - 1);
  }
  else if (shiftX > 0 && engine.printWorldToX > engine.layers[engine.selectedLayer].WORLD_WIDTH - shiftX)
  {
    shiftX = (engine.layers[engine.selectedLayer].WORLD_WIDTH - engine.printWorldToX);
  }
  if (shiftY < 0 && engine.printWorldFromY - 1 < -shiftY)
  {
    shiftY = -(engine.printWorldFromY - 1);
  }
  else if (shiftY > 0 && engine.printWorldToY > engine.layers[engine.selectedLayer].WORLD_LENGTH - shiftY)
  {
    shiftY = (engine.layers[engine.selectedLayer].WORLD_LENGTH - engine.printWorldToY);
  }
  engine.printWorldFromX += shiftX;
  engine.printWorldToX += shiftX;
  engine.printWorldFromY += shiftY;
  engine.printWorldToY += shiftY;
  if (shiftX != 0 || shiftY != 0)
  {
    engine.smartPrint = false;
  }
}

void print (MakerEngine & engine)
{
  if (!engine.smartPrint)
  {
    cout << term::cursor_move_to(1, 1) << term::CLEAR << flush;
  }
  engine.flat = engine.layers[0];
  for (int i = 0; i < engine.layers.size(); ++i)
  {
    for (int y = 1; y <= engine.layers[i].WORLD_LENGTH; ++y)
    {
      for (int x = 1; x <= engine.layers[i].WORLD_WIDTH; ++x)
      {
        string material = engine.layers[i].map[y][x];
        /*if (i != engine.selectedLayer)
        {
          int index = material.find(BLOCK);
          if (index != string::npos)
          {
            int a = material.find("\e[38;2;");
            int b = material.find("m", a);
            string col = material.substr(a, b - a + 1);
            material = col + "░" + term::RESET;
          }
        }*/
        if (material != "\0")
        {
          engine.flat.insert(x, y, material);
        }
      }
    }
  }
  engine.printManager.print(engine.flat, engine.viewportFromX, engine.viewportFromY, engine.printWorldFromX, engine.printWorldToX, engine.printWorldFromY, engine.printWorldToY, engine.smartPrint);
  if (!engine.smartPrint || engine.selectedMaterial != engine.prevSelectedMaterial)  
  {
    string border = (engine.materials[engine.selectedMaterial] != "\0" ? engine.materials[engine.selectedMaterial] : " ");
    for (int x = engine.viewportFromX - 1; x <= engine.viewportToX + 1; ++x)
    {
      cout << term::cursor_move_to(engine.viewportFromY - 1, x) << border << term::RESET << flush;
      cout << term::cursor_move_to(engine.viewportToY + 1, x) << border << term::RESET << flush;
    }
    for (int y = engine.viewportFromY - 1; y <= engine.viewportToY + 1; ++y)
    {
      cout << term::cursor_move_to(y, engine.viewportFromX - 1) << border << term::RESET << flush;
      cout << term::cursor_move_to(y, engine.viewportToX + 1) << border << term::RESET << flush;
    }
    engine.smartPrint = true;
  }
  int worldX, worldY;
  get_mouse_world_coordinates(engine, worldX, worldY);
  int prevWorldX, prevWorldY;
  get_prev_mouse_world_coordinates(engine, prevWorldX, prevWorldY);
  int termX, termY;
  get_mouse_terminal_coordinates(engine, termX, termY);
  termX = clamp(termX, engine.viewportFromX, clamp(engine.viewportToX, 1, engine.layers[engine.selectedLayer].WORLD_WIDTH + engine.viewportFromX - 1));
  termY = clamp(termY, engine.viewportFromY, clamp(engine.viewportToY, 1, engine.layers[engine.selectedLayer].WORLD_LENGTH + engine.viewportFromY - 1));
  int prevTermX, prevTermY;
  get_prev_mouse_terminal_coordinates(engine, prevTermX, prevTermY);
  prevTermX = clamp(prevTermX, engine.viewportFromX, clamp(engine.viewportToX, 1, engine.layers[engine.selectedLayer].WORLD_WIDTH + engine.viewportFromX - 1));
  prevTermY = clamp(prevTermY, engine.viewportFromY, clamp(engine.viewportToY, 1, engine.layers[engine.selectedLayer].WORLD_LENGTH + engine.viewportFromY - 1));
  if (worldX != prevWorldX || worldY != prevWorldY || engine.smartPrint)
  {
    cout << term::cursor_move_to(engine.terminalHeight, 2) << "World Coordinates: (" << worldX << ", " << worldY << ")" << flush;
    cout << term::cursor_move_to(prevTermY, prevTermX) << engine.layers[engine.selectedLayer].map[prevWorldY][prevWorldX] << flush;
    cout << term::cursor_move_to(termY, termX) << term::foreground_color(0, 0, 0) << term::background_color(127, 127, 127) << "+" << term::RESET << flush;
  }
}

void terminate_program (MakerEngine & engine, vector<void*> params)
{
  engine.terminate = true;
}

vector< tuple< int, INPUT_STATUS, void_function, vector<void*> > > KEY_COMBOS =
{
  {XK_Escape, PRESS, (void_function)&terminate_program, {}},
  {XK_b, REPEAT, (void_function)&brush_fill, {}},
  {XK_b, PRESS, (void_function)&backup, {}},
  {XK_f, PRESS, (void_function)&flood_fill, {}},
  {XK_r, PRESS, (void_function)&rectangle_fill, {}},
  {XK_l, PRESS, (void_function)&line_fill, {}},
  {XK_u, PRESS, (void_function)&undo_draw, {}},
  {XK_Right, PRESS, (void_function)&shift_viewport, {(void*)&DIRECTIONS[0][0], (void*)&DIRECTIONS[0][1]}},
  {XK_Left, PRESS, (void_function)&shift_viewport, {(void*)&DIRECTIONS[1][0], (void*)&DIRECTIONS[1][1]}},
  {XK_Down, PRESS, (void_function)&shift_viewport, {(void*)&DIRECTIONS[2][0], (void*)&DIRECTIONS[2][1]}},
  {XK_Up, PRESS, (void_function)&shift_viewport, {(void*)&DIRECTIONS[3][0], (void*)&DIRECTIONS[3][1]}},
  {XK_equal, PRESS, (void_function)&rotate_layer, {(void*)&ROTATE_RIGHT}},
  {XK_minus, PRESS, (void_function)&rotate_layer, {(void*)&ROTATE_LEFT}},
  {XK_bracketright, PRESS, (void_function)&rotate_material, {(void*)&ROTATE_RIGHT}},
  {XK_bracketleft, PRESS, (void_function)&rotate_material, {(void*)&ROTATE_LEFT}},
  {XK_n, PRESS, (void_function)&create_new_layer, {}},
  {XK_d, PRESS, (void_function)&delete_layer, {}},
  {XK_s, PRESS, (void_function)&magic_wand_select, {}},
  {XK_p, PRESS, (void_function)&paste, {}},
  {XK_Shift_L, PRESS, (void_function)&set_shift, {(void*)&TRUE}},
  {XK_Shift_L, RELEASE, (void_function)&set_shift, {(void*)&FALSE}},
};

void handle_key_presses (MakerEngine & engine)
{
  for (int i = 0; i < KEY_COMBOS.size(); ++i)
  {
    if (engine.inputManager.get_key_status(get<0>(KEY_COMBOS[i])) == get<1>(KEY_COMBOS[i]))
    {
      void (*func)(MakerEngine&, vector<void*>) = (void (*)(MakerEngine&, vector<void*>))(get<2>(KEY_COMBOS[i]));
      vector<void*> params = get<3>(KEY_COMBOS[i]);
      func(engine, params);
    }
  }
}

vector< tuple< pair<double, double>, string, INPUT_STATUS, void_function, vector<void*> > > BUTTONS =
{

};

int main (int argc, char ** argv)
{
  World world;
  string response;
  cout << "Load world from file (y/n) ";
  cin >> response;
  if (response == "y" || response == "Y")
  {
    cout << "File: ";
    cin >> response;
    world = World(response);
  }
  else if (response == "n" || response == "N")
  {
    int width, length;
    cout << "World dimension (width then length): ";
    cin >> width >> length;

    string fill;
    cout << "Fill world with: ";
    cin >> fill;

    world = World(width, length, fill);
  }
  cout << term::alternate_terminal() << term::cursor_hide() << flush;
  
  {
    MakerEngine engine(world);
    engine.calibrationManager.calibrate(engine.inputManager, 2);
    while (!engine.terminate)
    {
      update(engine);
      print(engine);
      handle_key_presses(engine);
    } 
    engine.inputManager.flush_stdin_until(27);
    world = engine.flat;
  }
  cout << term::cursor_move_to(1, 1) << term::CLEAR << term::cursor_show() << "Save? (y/n): " << flush;
  cin >> response;
  if (response.find("y") != string::npos || response.find("Y") != string::npos)
  {
    cout << term::cursor_move_to(1, 1) << term::CLEAR << "Save as: " << flush;
    cin >> response;
    if (response.length() > 0)
    {
      ofstream file(response.c_str());
      file << world.WORLD_LENGTH << " " << world.WORLD_WIDTH << endl;
      for (int i = 1; i <= world.WORLD_LENGTH; ++i)
      {
        for (int j = 1; j <= world.WORLD_WIDTH; ++j)
        {
          file << world.map[i][j] << endl;
        }
      }
      file.close();
    }
  }
  cout << term::normal_terminal() << flush;
  return 0;
}
