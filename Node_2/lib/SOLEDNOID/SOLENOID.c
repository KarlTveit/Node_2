				/*
 * SOLENOID.c
 *
 * Created: 08.11.2017 17:14:27
 *  Author: karlmt
 */ 
				
#include <avr/io.h>
#include "SOLENOID.h"
void SOLENOID_init(void){
	
	DDRB |= (1<<DDB4);	
	
}


void SOLENOID_disable(){
	
		PORTB &= ~(1 << PB4);
		
}

void SOLENOID_enable(){
	
	
	PORTB |= (1 << PB4);
}

