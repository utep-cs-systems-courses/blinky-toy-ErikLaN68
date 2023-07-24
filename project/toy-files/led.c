#include <msp430.h>
#include "led.h"
#include "statemachine.h"
#include "switches.h"

void
led_init()
{
  P1DIR |= LEDS;
  //Can't have this because the main is run so it sets it back to off all the time
}

void
both_leds_on()
{
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

void
toggle_leds()
{
  P1OUT ^= LED_GREEN;
  P1OUT ^= LED_RED;
}

void
only_green()
{
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;
}

void
only_red()
{
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
}

void
both_leds_off()
{
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
}
