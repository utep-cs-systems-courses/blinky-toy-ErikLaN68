#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "statemachine.h"
#include "switches.h"
#include "buzzer.h"

int main(void)
{
  //sets the clock up
  configureClocks();
  //sets the leds up but does not give them a value
  led_init();
  //sets the switches to take input
  switch_init();
  //sets the buzzer up to make noise
  buzzer_init();
  //enables the interrupts
  enableWDTInterrupts();
  
  or_sr(0x18);  // CPU off, GIE on
}
