#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

#define upOn 0
#define upOff 1
#define dnOn 2
#define dnOff 3

void main(void) 
{
  __enable_interrupt();
  configureClocks();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

char lightState = upOff;

void
both_lights_on()
{
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

void
both_lights_off()
{
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
}

void
up()
{
  switch (lightState) {
  case dnOn:
    lightState = upOn;
    //both_lights_off();
    break;
  case dnOff:
    lightState = upOff;
    //both_lights_off();
    break;
  }
}

void
down()
{
  switch (lightState) {
  case upOff:
    lightState = dnOn;
    both_lights_on();
    break;
  case upOn:
    lightState = dnOff;
    both_lights_off();
    break;
  }
}

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */
/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

  if (p1val & SW1) {
    if (lightState == upOff || lightState == upOn) {
      down();
    }
    if (lightState == dnOn || lightState == dnOff) {
      up();
    }
  }
  
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) { /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;   /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
    TA0R = 0;
    TA0CTL |= MC_1;
  }
}

__interrupt void Timer_A(void)
{
  TA0CTL &= ~MC_3;
  P1IE |= SWITCHES;
}
