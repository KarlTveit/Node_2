/*
 * TIMER.c
 *
 * Created: 25.10.2017 12:47:33
 *  Author: Administrator
 */ 

#include "TIMER.h"

static uint8_t stopwatch = 0;


void TIMER1_COMPA_vect() {
	stopwatch = stopwatch + 1;
} 


void TIMER_init() {
	
	TCCR1B |= (1 << WGM12); //CTC mode
	
	/*Want to count each second:
	Clock frequency = 16 000 000 and prescaler = 1024 ---> 16000000/1024 = 15625 ticks per sec*/
	
	//Defining top value of counter --> reset each second
	OCR1A = 15625;
	
	
	//Enable global interrupt
	sei();
	
	//Enable Timer Compare Match A Interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	 
	
}

void TIMER_start(){
	
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	stopwatch = 0;
	
	//Prescaler = 1024
	TCCR1B |= ((1 << CS10) | (1 << CS12));
	
}

void TIMER_stop() {
	
	//Turning off clock source
	TCCR1B &= ~(1<<CS40) & ~(1 << CS41) & ~(1 << CS42);
	
}

