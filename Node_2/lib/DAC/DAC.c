/*
 * DAC.c
 *
 * Created: 08.11.2017 12:47:43
 *  Author: karlmt
 */ 
#include "DAC.h"
#define MAX520_ADDR 0b01011110

void DAC_init(void){
	TWI_Master_Initialise();
	sei();
}

void DAC_write(uint8_t data){
	uint8_t msg[3] ={MAX520_ADDR,0,data};
	TWI_Start_Transceiver_With_Data(msg,3);
}