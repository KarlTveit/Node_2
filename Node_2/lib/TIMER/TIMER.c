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
	
	
	//CTC mode for highscore_timer
	TCCR4B |= (1 << WGM42); 
	
	//Normal mode for pid_timer (WGM2(2:0) = 0)
	
	
	/*Want to count each second:
	Clock frequency = 16 000 000 and prescaler = 1024 ---> 16000000/1024 = 15625 ticks per sec*/
	
	//Defining top value of counter for highscore_timer --> reset each second
	OCR4A = 15625;
	//Defining top value of counter for pid_timer --> reset each 1/25 second
	OCR2A = 625;
	
	//Enable global interrupt
	sei();
	
	//Enable Timer Compare Match A Interrupt for highscore_timer
	TIMSK4 |= (1 << OCIE4A);
	
	//Enable Timer Overflow Interrupt for pid_timer 
	TIMSK2 |= (1 << TOIE2);
	
}

void TIMER_start(timer_t timer){
	
	stopwatch = 0;
	
	if (timer == highscore_timer) {
		TCNT4H = 0x00;
		TCNT4L = 0x00;
		
		//Prescaler = 1024
		TCCR4B |= (1 << CS40) | (1 << CS42);
	}
	else if (timer == pid_timer) {
	
		//Prescaler = 1024
		TCCR2B |= (1 << CS20) | (1 << CS22);
	}
	
	
}

void TIMER_stop() {
	
	//Turning off clock source
	TCCR4B &= ~(1<<CS40) & ~(1 << CS41) & ~(1 << CS42);
	

}



uint16_t TIMER_get_time() {
	return stopwatch;
}
