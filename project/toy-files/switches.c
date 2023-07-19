#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "statemachine.h"

char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler()
{
  //Checks when the switches are up
  char p2val = switch_update_interrupt_sense();
  switchDown1 = (p2val & SW1) ? 0 : 1;
  switchDown2 = (p2val & SW2) ? 0 : 1;
  switchDown3 = (p2val & SW3) ? 0 : 1;
  switchDown4 = (p2val & SW4) ? 0 : 1;
  
  state_update();
  
  switchChanged = 1;
}
