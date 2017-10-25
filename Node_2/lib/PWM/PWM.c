/*
 * PWM.c
 *
 * Created: 25.10.2017 10:07:05
 *  Author: Administrator
 */ 

#include "PWM.h"


//#ifdef __AVR_ATmega162__

void PWM_init(void) { 
	
	
	//Enable fast mode
	TCCR1A &= ~(1<<WGM10);	
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);		
	
	//Compare Output Mode: Non-inverting
	TCCR1A |= (1<<COM1A1);			
	
	
	//Prescaler: clk/1024
	TCCR1B |= (1<<CS12);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS10);

	//Top value = F_CPU/(N*(1/min_period)) , N=1024
	ICR1 = 312;
	OCR1A = 100;
	
	
	//Setting pin 11 (PB5) to output
	DDRB |= (1<<PB5);
	
	
	// Enable global interrupts
	//sei();
	
	
	
}









/*#endif*/