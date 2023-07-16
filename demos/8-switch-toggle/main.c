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
  enableWDTInterrupts();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

//Used for the state of switch
char lightState = upOff;
char green = 0;
char red = 0;
char pressCount = 0;

//Counts to 1000 to stop switch bounce
void
counter()
{
  int count = 0;
  while (count <1000) {
    count++;
  }
}

//Turns the lights on
void
both_lights_on()
{
  //P1OUT |= LED_GREEN;
  //P1OUT |= LED_RED;
  green = 1;
  red = 1;
}

//Turns the lights off
void
both_lights_off()
{
  //P1OUT &= ~LED_GREEN;
  //P1OUT &= ~LED_RED;
  green = 0;
  red = 0;
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
    both_lights_on();
    break;
  case upOn:
    //If lights were on when switch up then ligths off
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

  //Checks that SW1 was pressed and then turns the lights either on or off
  if (p1val & SW1) {
    if (lightState == upOff || lightState == upOn) {
      pressCount++;
      down();
    }
    if (lightState == dnOn || lightState == dnOff) {
      up();
    }
  }
  
}

void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  //Checks the port 1 interrupt flag with switch bits to see if a switch caused it
  if (P1IFG & SWITCHES) {
    //counts an int up to 1000 to help with switch bounce
    counter();
    //Sets the port 1 interrupt to check for another interrupt
    P1IFG &= ~SWITCHES;
    //Goes to the switch_interrupt_handler
    switch_interrupt_handler();
    //Turns the interrupt off for the switches to stop switch bounce
    P1IE &= ~SWITCHES;
  }
  //Turns the interrupt of the switches back on
  P1IE |= SWITCHES; 
}

void
blink_state()
{
  if (pressCount == 1) {
    
    if (green & red) {
      P1OUT ^= LED_GREEN;
      P1OUT &= ~LED_RED;
    }
    else {
      P1OUT &= ~LED_GREEN;
      P1OUT &= ~LED_RED;
    }
    
  }
  else {
    
    if (green & red) {
      P1OUT ^= LED_GREEN;
      P1OUT ^= LED_RED;
    }
    else {
      P1OUT &= ~LED_GREEN;
      P1OUT &= ~LED_RED;
    }
  }

  if (pressCount == 4) {
    pressCount = 0;
  }
  
}

void
__interrupt_vec(WDT_VECTOR) WDT()
{
  blink_state();
}

