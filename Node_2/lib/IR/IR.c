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

volatile static bool IR_intflag = false;




void IR_init(void){
	ADCSRA	|=	(1<<ADEN)
			|	(1<<ADPS0)
			|	(1<<ADPS1)
			|	(1<<ADPS2);
	DDRF &= ~(1<<PF0);
	ADMUX |= (1<< REFS0);
	
	sei();
	
	ADCSRA |= (1<<ADIE);
	ADCSRA &= ~(1<<ADIF);
	
	
}
uint8_t IR_read(void){
	//uint8_t low;
	//uint16_t high;
	ADCSRA |= (1<<ADSC);
	
	if (IR_intflag) {
		IR_intflag = false;
		can_message_t node_2_msg;
		node_2_msg.id = 70;
		node_2_msg.length = 1;
		node_2_msg.data[0] = 1;
		CAN_send_message(&node_2_msg);
		return ADC;
	};
		
		
	return 0;
	
	}
	
ISR(ADC_vect){
	IR_intflag = true;
}