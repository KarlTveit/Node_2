#include "ADC.h"
#include <avr/io.h>
volatile uint8_t interrupt_flag;

#define ADC_START_ADDRESS 0x1400

void ADC_init(void){
	ADCSRA	|=	(1<<ADEN)
			|	(1<<ADPS0)
			|	(1<<ADPS1)
			|	(1<<ADPS2);
}


uint8_t ADC_read(channel ch){
	ADMUX = (1<< REFS0) | (ch & 0x1f);
	
	ADCSRA |=	(1<< ADSC);
	
	while( (ADCSRA & (1<<ADSC)) ) {}
		
	return ADC;
}




ISR(INT2_vect){
	interrupt_flag = 0;
}