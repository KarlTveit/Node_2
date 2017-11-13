/*
 * TIMER.h
 *
 * Created: 25.10.2017 12:47:46
 *  Author: Administrator
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include<avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>

ISR(TIMER1_COMPA_vect);


void TIMER_init();
void TIMER_start();
void TIMER_stop();



#endif /* TIMER_H_ */