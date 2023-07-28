#include <msp430.h>
#include "switches.h"

/*Checks to see if a switch was pressed*/
void
__interrupt_vec(PORT2_VECTOR) Port_2()
{
  //counter();
  //Turns the interrupt off for the switches to stop switch bounce
  P2IE &= ~SWITCHES;
  //Checks the port 2 interrupt flag with switch 1 to see if a switch caused it
  if (P2IFG & SWITCHES) {
    //counts an int up to 1000 to help with switch bounce
    //counter();
    //Sets the port 2 interrupt to check for another interrupt
    P2IFG &= ~SWITCHES;
    //Goes to the switch_interrupt_handler
    switch_interrupt_handler();
  }
  //Turns the interrupt of the switches back on
  P2IE |= SWITCHES;
}
