#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;
char lightState;

//Getting error where the program thinks the switch is still down when pressed multiple times.
//Need to make a statemachine to handle this that works as a toggle for all the switchs
void
state_update()
{
  if (switchDown1) {
    state_machine_1(0);
    /*play_song(500);
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED; */
    //light_state_check_sw1();
    //P1OUT &= ~LED_GREEN;
    //P1OUT &= ~LED_RED;
  }
  else if (switchDown2) {
    //state_machine_1(1);
    //buzzer_on();
    play_song(475);
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
  else if (switchDown3) {
    //state_machine_1(1);
    //buzzer_on();
    play_song(450);
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
  }
  else if (switchDown4) {
    //state_machine_1(1);
    //buzzer_on();
    play_song(0);
    both_leds_off();
  }
  else {
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}

//State machine for when the switch goes up
void
up()
{
  //keeps track of the up states
  switch (lightState) {
  case dnOn:
    lightState = upOn;
    break;
  case dnOff:
    lightState = upOff;
    break;
  }
}

//State machine for when the switch goes down

void
down()
{
  switch (lightState) {
  case upOff:
    //if the lights were off when switch up then lights on
    lightState = dnOn;
    both_leds_on();
    break;
  case upOn:
    //If lights were on when switch up then ligths off
    lightState = dnOff;
    both_leds_off();
    break;
  }
}

void
light_state_check_sw1()
{
  if (lightState == upOff || lightState == upOn) {
    down();
  }
  if (lightState == dnOn || lightState == dnOff) {
    up();
  }
}

void
state_machine_1(char stop)
{
  short count = 1500;
  char smallCount = 0;
  while (count > 0) {
    if (smallCount < 50){
      play_song(15000);
    }
    else {
      play_song(13000);
      if (smallCount == 100) {
	smallCount = 0;
      }
    }
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
    count--;
    smallCount++;
  }
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
  return;
}
