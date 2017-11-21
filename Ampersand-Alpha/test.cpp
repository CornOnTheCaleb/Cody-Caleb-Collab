#include "character.h"
#include "utility/keyboardmanager.h"
#include "utility/timemanager.h"

// compile with -lpthread flag
int main()
{
  World fuck;//("first_try.txt");
  Character ampersand;//(term::background_color(32, 79, 155) + "&" + term::RESET, 2, TERMINAL_LENGTH - 3);
  TimeManager time;
  KeyboardManager keyboard("/dev/input/event0");

  
  keyboard.init(); // gets keyboard input
  cout << term::alternate_terminal() << term::cursor_hide(); // switches to alternate terminal << hides cursor
  while(true)
  {
    time.update();

    if(keyboard.get_key_state(KEY_A))
      ampersand.move('a', fuck, time);
    if(keyboard.get_key_state(KEY_D))
      ampersand.move('d', fuck, time);
    if(keyboard.get_key_state(KEY_W))
      ampersand.move('w', fuck, time);
    if(keyboard.get_key_state(KEY_ESC))
    {
      keyboard.terminate(27);
      break;
    }
    
    system("clear");
    cout << "\e[1;1H";
    fuck.print();//ampersand.get_x_coord(), ampersand.get_y_coord());
    cout << flush;
    
    ampersand.update_character(fuck, time);
    usleep(1000);//00);
  }
  cout << term::normal_terminal() << term::cursor_show(); //<< "\e[?25h"; // switches to original terminal << shows cursor
  return 0;
}
