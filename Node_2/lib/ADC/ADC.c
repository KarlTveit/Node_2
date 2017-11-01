#include "ADC.h"
#include <avr/io.h>
volatile uint8_t interrupt_flag;

#define ADC_START_ADDRESS 0x1400

void ADC_init(void){
	ADCSRA	|=	(1<<ADEN)
			|	(1<<ADPS0)
			|	(1<<ADPS1)
			|	(1<<ADPS2);
	DDRF &= ~(1<<PF0);
	ADMUX |= (1<< REFS0);
	ADCSRA |= (1<<ADIE);
	ADCSRA &= ~(1<<ADIF);
	
}


uint8_t ADC_read(channel ch){
	 /*| (ch & 0x1f)*/
	
	ADCSRA |=	(1<< ADSC);
	
	while( (ADCSRA & (1<<ADSC)) ) {}
		
	return ADC;
}




ISR(INT2_vect){
	interrupt_flag = 0;
}