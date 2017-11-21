/*
 * DAC.c
 *
 * Created: 08.11.2017 12:47:43
 *  Author: karlmt
 */ 
#include "DAC.h"



void DAC_init(void){
	
	//Enable Global Interrupts
	sei();
	
	TWI_Master_Initialise();
	
}

void DAC_write(uint8_t data){
	
	uint8_t msg[TWI_msg_size] = {MAX520_ADDR,0,data};
		
	TWI_Start_Transceiver_With_Data(msg,TWI_msg_size);
	
}