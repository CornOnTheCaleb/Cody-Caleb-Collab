//#include "character.h"
#include "enemy.h"
#include "utility/inputmanager.h"
#include "utility/timemanager.h"
#include "utility/printmanager.h"

// compile with -lX11 flag
int main()
{
  World world("second_try.txt");
  Character ampersand(term::foreground_color(255, 0, 0) + "&" + term::RESET, term::background_color(32, 79, 155), 2, TERMINAL_LENGTH - 3, 20);
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
      ampersand.move('a', world, time);
    if(input.get_key_state(XK_d))
      ampersand.move('d', world, time);
    if(input.get_key_state(XK_w))
      ampersand.move('w', world, time);
    if(input.get_key_state(XK_Escape))
    {
      input.flush_stdin_until(27);
      break;
    }
    fuckface.move(world, time, ampersand);
     
    ampersand.update_character(world, time);
    fuckface.update_character(world, time);
    printer.print(world, 1, 1, true);
    /*cout << "\e[1;1H";
    fuck.print();//ampersand.get_x_coord(), ampersand.get_y_coord());
    cout << flush;*/
   
    // usleep(50000);
  }
  cout << term::normal_terminal() << term::cursor_show(); //<< "\e[?25h"; // switches to original terminal << shows cursor
  return 0;
}
