#ifndef led_included
#define led_included

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

extern char green, red;


void led_init();
void both_leds_on();
void both_leds_off();

#endif
