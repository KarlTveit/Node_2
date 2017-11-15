/*
 * TIMER.c
 *
 * Created: 25.10.2017 12:47:33
 *  Author: Administrator
 */ 

#include "TIMER.h"

uint16_t volatile static stopwatch = 0;


ISR(TIMER4_COMPA_vect) {
	stopwatch = stopwatch + 1;
	_delay_ms(1);
	/*printf("Interrupt vector func\n\n");*/
} 
/*
ISR(TIMER4_OVF_vect){
	stopwatch = stopwatch + 1;
	printf("Interrupt vector func\n\n");
}*/





void TIMER_init() {
	
	TCCR4B |= (1 << WGM42); //CTC mode
	
	/*Want to count each second:
	Clock frequency = 16 000 000 and prescaler = 1024 ---> 16000000/1024 = 15625 ticks per sec*/
	
	//Defining top value of counter --> reset each second
	OCR4A = 15625;
	
	
	//Enable global interrupt
	sei();
	
	//Enable Timer Compare Match A Interrupt
	TIMSK4 |= (1 << OCIE4A);

	
	 
	
}

void TIMER_start(){
	
	TCNT4H = 0x00;
	TCNT4L = 0x00;
	
	stopwatch = 0;
	
	//Prescaler = 1024
	TCCR4B |= (1 << CS40) | (1 << CS42);
	
}

void TIMER_stop() {
	
	//Turning off clock source
	TCCR4B &= ~(1<<CS40) & ~(1 << CS41) & ~(1 << CS42);
	

}



void TIMER_get_time() {
	return stopwatch;
}
