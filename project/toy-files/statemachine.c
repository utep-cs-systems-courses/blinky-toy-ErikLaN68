#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "submachine.h"

char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;
char lightState;

//Getting error where the program thinks the switch is still down when pressed multiple times.
//Need to make a statemachine to handle this that works as a toggle for all the switchs
void
state_update(char state)
{
  switch (state) {
  case 1:
    sub_machine_1();
    state = 0;
    break;
  case 2:
    sub_machine_2();
    state = 0;
    break;
  case 3:
    sub_machine_3();
    state = 0;
    break;
  case 4:
    play_song(0);
    both_leds_off();
    state = 0;
    break;
  default:
    break;
  }
}

/*
void
state_machine_1()
{
  short count = 1500;
  char smallCount = 0;
  char secondCount = 0;
  short songFr = 15000;
  while (count > 0) {
    if (count > 950) {
      if (smallCount < 50){
	play_song(15000);
	P1OUT |= LED_GREEN;
	P1OUT &= ~LED_RED;
      }
      else {
	play_song(13000);
	P1OUT &= ~LED_GREEN;
	P1OUT |= LED_RED;
	if (smallCount == 100) {
	  smallCount = 0;
	}
      }
    }
    else {
      play_song(songFr);
      P1OUT |= LED_GREEN;
      P1OUT |= LED_RED;
      if (secondCount == 50) {
	songFr -= 300;
	short wait = 10000;
	while (wait > 0) {
	  P1OUT &= ~LED_GREEN;
	  P1OUT &= ~LED_RED;
	  wait--;
	}
	secondCount = 0;
      }
    }
    count--;
    smallCount++;
    secondCount++;
  }
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
  return;
}*/
 /*
void
state_machine_2()
{
  play_lazer();
  char count = 25;
  while (count > 0) {
    lazer();
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
    count--;
  }
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
  return;
}*/
