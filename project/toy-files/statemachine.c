#include <msp430.h>
//#include "statemachine.h"
//#include "led.h"
#include "switches.h"
//#include "buzzer.h"
#include "submachine.h"

//char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;
//char lightState;

//Takes the given state value and then goes to the correct statemachine
void
state_update(char state)
{
  switch (state) {
  case 1:
    sub_machine_1();
    state = 0;
    break;
  case 2:
    sub_machine_2();
    state = 0;
    break;
  case 3:
    sub_machine_3();
    state = 0;
    break;
  case 4:
    play_song(0);
    both_leds_off();
    state = 0;
    break;
  default:
    break;
  }
}
