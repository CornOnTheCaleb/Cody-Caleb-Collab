#define DEBUG

#include "character.h"
#include "enemy.h"
#include "utility/inputmanager.h"
#include "utility/timemanager.h"
#include "utility/printmanager.h"

using namespace std;

#ifdef DEBUG
void print_debug (World & world, Character * c, const string header, const int line, const int column)
{
  cout << term::cursor_move_to(line + 0, column) << header << string(10, ' ') << flush;
  cout << term::cursor_move_to(line + 1, column) << "~ previous position: (" << (int)c->x_coord_prev << ", " << (int)c->y_coord_prev << ")\t(" << c->x_coord_prev << ", " << c->y_coord_prev << ")" << string(10, ' ') << flush;
  cout << term::cursor_move_to(line + 2, column) << "~ current position: (" << (int)c->x_coord << ", " << (int)c->y_coord << ")\t(" << c->x_coord << ", " << c->y_coord << ")" << string(10, ' ') << flush;
  cout << term::cursor_move_to(line + 3, column) << "~ velocity: (" << c->x_velocity << ", " << c->y_velocity << ")" << string(10, ' ') << flush;
  cout << term::cursor_move_to(line + 4, column) << "~ surroundings: above [" << world.map[(int)c->y_coord - 1][(int)c->x_coord] << "] below [" << world.map[(int)c->y_coord + 1][(int)c->x_coord] << "] left [" << world.map[(int)c->y_coord][(int)c->x_coord - 1] << "] right [" << world.map[(int)c->y_coord][(int)c->x_coord + 1] << "]" << string(10, ' ') << flush;
:x  cout << term::cursor_move_to(line + 5, column) << "~ covered: [" << c->covered << "]" << string(10, ' ') << flush;
  cout << term::cursor_move_to(line + 6, column) << "~ jumped: " << (c->jumped ? "TRUE" : "FALSE") << string(10, ' ') << flush;
}
#endif

// compile with -lX11 flag
int main(int argc, char ** argv)
{
  World world("second_try.txt");
  Character hero(term::foreground_color(255, 0, 0) + "&" + term::RESET, term::background_color(32, 79, 155), 2, TERMINAL_LENGTH - 3, 20);
  Enemy fuckface(term::foreground_color(255, 0, 0) + "#" + term::RESET, term::background_color(32, 79, 155), 10, TERMINAL_LENGTH - 3, 10);
  TimeManager time;
  InputManager input;
  PrintManager printer;
  
  cout << term::alternate_terminal() << term::cursor_hide(); // switches to alternate terminal << hides cursor
  while(true)
  {
    input.update();
    time.update();

    if(input.get_key_state(XK_a))
      hero.move('a', world, time);
    if(input.get_key_state(XK_d))
      hero.move('d', world, time);
    if(input.get_key_state(XK_w))
      hero.move('w', world, time);
    if(input.get_key_state(XK_Escape))
    {
      input.flush_stdin_until(27);
      break;
    }
    fuckface.move(world, time, hero);
     
    hero.update_character(world, time);
    fuckface.update_character(world, time);
    printer.print(world, 1, 1, true);
  
#ifdef DEBUG
    cout << term::cursor_move_to(56, 1) << "delta time: " << time.get_delta_time() << endl;
    print_debug(world, &hero, "HERO VARIABLES", 58, 1);
    print_debug(world, &fuckface, "ENEMY VARIABLES", 58, 70);
#endif
  }
  cout << term::normal_terminal() << term::cursor_show(); //<< "\e[?25h"; // switches to original terminal << shows cursor
  return 0;
}
