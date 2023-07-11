//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count time
int secondCount = 0;
char greenOn = 1;
char redOn = 1;

void binary_zero()
{
  greenOn = 0;
  redOn = 0;
}

void binary_one()
{
  greenOn = 1;
}

void binary_two()
{
  greenOn = 0;
  redOn = 1;
}

void binary_three()
{
  greenOn = 1;
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  if (secondCount >= 0 && secondCount < 500) {
    binary_zero();
  }
  if (secondCount >= 500 && secondCount < 1000) {
    binary_one();
  }
  if (secondCount >= 1000 && secondCount < 1500) {
    binary_two();
  }
  if (secondCount >= 1500 && secondCount < 2000) { 
    binary_three();
  }
  if (secondCount == 2000) {
    secondCount = 0;
  }
  secondCount++;
  
  if (greenOn)
    P1OUT ^= LED_GREEN;
  else
    P1OUT &= ~LED_GREEN;

  if (redOn)
    P1OUT ^= LED_RED;
  else
    P1OUT &= ~LED_RED;
}
