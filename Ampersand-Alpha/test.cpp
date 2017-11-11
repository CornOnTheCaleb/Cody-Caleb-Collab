#include "character.h"
#include "utility/keyboardmanager.h"
#include "utility/timemanager.h"

int main()
{
  World fuck;
  Character ampersand;
  TimeManager time;
  KeyboardManager keyboard("/dev/input/event0");

  keyboard.init(); // gets keyboard input
  cout << "\e[?1049h" << "\e[?25l"; // switches to alternate terminal << hides cursor
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
    
    cout << "\e[1;1H";
    fuck.print();
    
    ampersand.update_character(fuck, time);
    usleep(100000);
  }
  cout << "\e[?1049l" << "\e[?25h"; // switches to original terminal << shows cursor
  return 0;
}
