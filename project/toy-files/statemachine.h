#ifndef stateMachines_included
#define stateMachines_included

#define upOn 0
#define upOff 1
#define dnOn 2
#define dnOff 3

extern char lightState;

void state_update();
void light_state_check_sw1();
void state_machine_1(char stop);

#endif
