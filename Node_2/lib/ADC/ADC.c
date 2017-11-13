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
	ADMUX &= ~(1 << REFS1);
	
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
	ADCSRB &= ~(1 << MUX5);
	
	ADCSRA |= (1<<ADIE);
	//ADCSRA &= ~(1<<ADIF);
	
	
	
	
	ADMUX |= (1 << ADLAR);	//sets left adjust result
}


uint8_t ADC_read(channel ch){
	 /*| (ch & 0x1f)*/
	
	ADCSRA |=	(1<< ADSC);
	
	while( (ADCSRA & (1<<ADSC)) ) {}
		
	return ADCH;
}




ISR(INT2_vect){
	interrupt_flag = 0;
}