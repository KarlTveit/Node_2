/*
 * IR.c
 *
 * Created: 01.11.2017 09:59:06
 *  Author: karlmt
 */ 
#include "IR.h"
#include "../ADC/ADC.h"
#include <stdbool.h>
#include <avr/interrupt.h>






void IR_init(void){
	
	ADC_init();
	
}

uint8_t IR_read(void){
	
	//Start conversion
	ADCSRA |= (1<<ADSC);	
	
	while (ADCSRA & (1<<ADSC)) {};
	
	return ADCH;
	
}
	
