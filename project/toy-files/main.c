#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "statemachine.h"
#include "switches.h"
#include "buzzer.h"

void
main(void)
{
  configureClocks();
  led_init();
  switch_init();
  buzzer_init();
  //buzzer_set_period(1000);
  enableWDTInterrupts();
  
  or_sr(0x18);  // CPU off, GIE on
}
