	.data
	.align 2		;Dont think this needed but put if needed
	.extern state		;state variable used in switch

	.extern sub_machine_1	;all the machine methods that could be called
	.extern sub_machine_2
	.extern sub_machine_3
	.extern sub_machine_4
	.text
	
state_update:
	cmp #1,&state		;works like a switch statement
	jz sub1			;jumps if equal to zero
	cmp #2,&state
	jz sub2
	cmp #3,&state
	jz sub3
	cmp #4,&state
	jz sub4
	jmp out			;takes you back at the end
	
sub1:
	call #sub_machine_1
	jmp out
sub2:
	call #sub_machine_2
	jump out
sub3:
	call #sub_machine_3
	jmp out
sub4:
	call #sub_machine_4
	jmp out
out:
	mv #0,&state		;sets the state variable to zero
	pop r0
