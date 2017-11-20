#include "ADC.h"
#include <avr/io.h>
volatile uint8_t interrupt_flag;

#define ADC_START_ADDRESS 0x1400

void ADC_init(void){
	
	//ADC enable
	ADCSRA	|=	(1 << ADEN);
	
	//Selecting prescaler: f_clk/128
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	
	//Setting PF0 to input pin
	DDRF &= ~(1 << PF0);
	
	//Selecting voltage reference to AVCC with external capacitor at AREF pin
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0);
	
	//Selecting ADC0 as input channel
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
	ADCSRB &= ~(1 << MUX5);
	
	//Left adjusted result
	ADMUX |= (1 << ADLAR);
		
}


uint8_t ADC_read(channel ch){
	
	//Starting conversion
	ADCSRA |=	(1 << ADSC);
	
	//Waiting for conversion to complete
	while( (ADCSRA & (1 << ADSC)) ) {}
	
	//The result is written to ADCH (left adjusted)	
	return ADCH;
	
}

