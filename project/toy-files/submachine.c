#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "wdinterhandler.h"

void
sub_machine_1()
{
  short count = 1500;
  char smallCount = 0;
  char secondCount = 0;
  short songFr = 15000;
  while (count > 0) {
    if (count > 950) {
      if (smallCount < 50){
	play_song(15000);
	only_green();
      }
      else {
	play_song(13000);
	only_red();
	if (smallCount == 100) {
	  smallCount = 0;
	}
      }
    }
    else {
      play_song(songFr);
      both_leds_on();
      if (secondCount == 50) {
	songFr -= 300;
	short wait = 10000;
	while (wait > 0) {
	  both_leds_off();
	  wait--;
	}
	secondCount = 0;
      }
    }
    count--;
    smallCount++;
    secondCount++;
  }
  both_leds_off();
  only_green();
  play_song(0);
}

void
sub_machine_2()
{
  char count = 100;
  //was count > 0
  while (count > 0) {
    if (count < 25) {
      lazer(1);
      //toggle_leds();
    }
    else if (count < 50) {
      lazer(2);
      //toggle_leds();
    }
    else if (count < 75) {
      lazer(3);
      //toggle_leds();
    }
    else {
      lazer(4);
      //toggle_leds();
    }
    toggle_leds();
    count--;
  }
  both_leds_off();
  only_red();
  play_song(0);
}

void
sub_machine_3()
{
  short mainCount = 10000;
  short count = 0;
  while (mainCount > 0) {
    if (count == 100) {
      P1OUT ^= LED_GREEN;
      short_play(1700);
      __delay_cycles(20000);
      count = 0;
    }
    else {
      //short_play(1000);
      P1OUT ^= LED_RED;
    }
    count++;
    mainCount--;
  }
  short_play(0);
}
