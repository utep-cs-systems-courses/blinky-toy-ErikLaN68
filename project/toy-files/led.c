#include <msp430.h>
#include "led.h"
#include "statemachine.h"
#include "switches.h"

//Sets the leds in the main
void
led_init()
{
  P1DIR |= LEDS;
  //Can't have this because the main is run so it sets it back to off all the time
}

//Turns both leds on
void
both_leds_on()
{
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

//toggles both leds
void
toggle_leds()
{
  P1OUT ^= LED_GREEN;
  P1OUT ^= LED_RED;
}

//turns green on and turns red off
void
only_green()
{
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;
}

//turns red on and turns green off
void
only_red()
{
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
}

//turns both leds off
void
both_leds_off()
{
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
}
