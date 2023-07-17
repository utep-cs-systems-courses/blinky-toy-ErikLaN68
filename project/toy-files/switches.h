#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES (SW1 | SW2 | SW3 | SW4)   /* 4 switchs on top board */

extern char switchDown1,switchDown2,switchDown3,switchDown4,switchChanged;

#endif
