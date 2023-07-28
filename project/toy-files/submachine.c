#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void
sub_machine_1()
{
  //Variables used to control song
  short count = 1500;
  char smallCount = 0;
  char secondCount = 0;
  short songFr = 15000;
  //Main loop that runs the song
  while (count > 0) {
    //Will play a song if only count is greater than 950
    if (count > 950) {
      //Small count is used switch between two songs and different lights
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
      //plays this once the count is less than 950
      play_song(songFr);
      both_leds_on();
      //lowers the songFr every time the second count hits 50
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
  //Once done the green led is left on and the buzzer is turned off
  both_leds_off();
  only_green();
  play_song(0);
}

void
sub_machine_2()
{
  char count = 100;
  //Controls how long the song plays
  while (count > 0) {
    //Used to change the sound of the song
    if (count < 25) {
      lazer(1);
    }
    else if (count < 50) {
      lazer(2);
    }
    else if (count < 75) {
      lazer(3);
    }
    else {
      lazer(4);
    }
    //while buzzer changes the leds are toggled
    toggle_leds();
    count--;
  }
  //Once done the red led is left on and the buzzer is turned off
  both_leds_off();
  only_red();
  play_song(0);
}

void
sub_machine_3()
{
  short mainCount = 10000;
  short count = 0;
  //Used to run the machine
  while (mainCount > 0) {
    //if count is 100 then toggle Green led
    if (count == 100) {
      P1OUT ^= LED_GREEN;
      short_play(1700);
      //delays the msp430
      __delay_cycles(20000);
      count = 0;
    }
    else {
      //short_play(1000);
      //toggles the red led
      P1OUT ^= LED_RED;
    }
    count++;
    mainCount--;
  }
  //turns the led off
  short_play(0);
}
