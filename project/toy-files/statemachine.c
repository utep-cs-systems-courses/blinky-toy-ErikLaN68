#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
//#include "buzzer.h"

char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;
char lightState;

void
state_update()
{
  if (switchDown1) {
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
    //light_state_check_sw1();
  }
  else if (switchDown2) {
    P1OUT |= LED_GREEN;
  }
  else if (switchDown4) {
    P1OUT |= LED_RED;
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
