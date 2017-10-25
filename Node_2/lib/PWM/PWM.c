/*
 * PWM.c
 *
 * Created: 25.10.2017 10:07:05
 *  Author: Administrator
 */ 

#include "PWM.h"

#include "../CAN/CAN.h"


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
	ICR1 = 312;											// 312 implies 20 ms = T
	OCR1A = PWM_mid;									// The duty cycle is set here (15.6-32.1 implies 1ms-2ms)
	
	
	//Setting pin 11 (PB5) to output
	DDRB |= (1<<PB5);
	
	
	// Enable global interrupts
	//sei();
	
	
	
}



float PWM_get_duty_cycle(void) {
	
	can_message_t msg;
	
	if(MCP2515_read(MCP_CANINTF) & 1){
		CAN_recieve_data(&msg);
		CAN_print_message(msg);
		MCP2515_bit_modify(MCP_CANINTF,0x1,0x1);	
	}
	float x_pos = msg.data[0];
	printf("x_pos = %d\n", x_pos);
	return (x_pos/255)*(PWM_max-PWM_min) + PWM_min;
	
}


void PWM_set_duty_cycle(float val) {
	
	if (val >= PWM_max) {
		OCR1A = PWM_max;
	}
	else if (val <= PWM_min) {
		OCR1A = PWM_min;
	}
	else {
		OCR1A = (uint8_t) val;	
	}
	
}







/*#endif*/