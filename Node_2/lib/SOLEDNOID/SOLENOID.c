				/*
 * SOLENOID.c
 *
 * Created: 08.11.2017 17:14:27
 *  Author: karlmt
 */ 
				
#include <avr/io.h>
#include "SOLENOID.h"
void SOLENOID_init(void){
	
	DDRA |= (1<<DDA1);	
	
}


void SOLENOID_enable(){
	
		PORTA |= (1 << PA1);
		
}

void SOLENOID_disable(){
	
	PORTA &= ~(1 << PA1);
}