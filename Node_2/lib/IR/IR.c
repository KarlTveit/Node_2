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
	ADMUX &= ~(1 << REFS1);
	
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
	ADCSRB &= ~(1 << MUX5);
	
	sei();
	
	ADCSRA |= (1<<ADIE);
	ADCSRA &= ~(1<<ADIF);
	
	ADMUX |= (1 << ADLAR);
}
uint8_t IR_read(void){
	//uint8_t low;
	//uint16_t high;
	ADCSRA |= (1<<ADSC);	//Start conversion
	
	while (ADCSRA & (1<<ADSC)) {};
	
	return ADCH;
	
	/*if (IR_intflag) {
		IR_intflag = false;
		can_message_t node_2_msg;
		node_2_msg.id = 70;
		node_2_msg.length = 1;
		node_2_msg.data[0] = 1;
		CAN_send_message(&node_2_msg);
		return ADC;
	};
		*/
		

	}
	
ISR(ADC_vect){
	IR_intflag = true;
}