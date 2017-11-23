/*
 * Node_2.c
 *
 * Created: 18.10.2017 15:14:10
 *  Author: karlmt
 */ 




#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "stdio.h"


#include "../lib/PWM/PWM.h"
#include "../lib/UART/UART.h"
#include "../lib/ADC/ADC.h"
#include "../lib/SRAM/SRAM.h"
#include "../lib/SPI/SPI.h"
#include "../lib/MCP2515/MCP2515.h"
#include "../lib/CAN/CAN.h"
#include "../lib/IR/IR.h"
#include "../lib/DAC/DAC.h"
#include "../lib/TWI/TWI_Master.h"
#include "../lib/TIMER/TIMER.h"
#include "../lib/SOLEDNOID/SOLENOID.h"
#include "../lib/HC05/HC05.h"
#include "../lib/DEFINITIONS.h"
uint8_t RECEIVED = 0;



int main(void) {
	
	//Setting port A to output
	DDRA = OUTPUT_ENABLE_ALL;
	
	//Initializing all drivers
	UART_init(UBRR);
	HC05_init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	CAN_init();
	PWM_init();
	DAC_init();
	MOTOR_init();
	IR_init();
	SOLENOID_init();
	TIMER_init();
	
	

	//Initializing variables
	//uint8_t game_enable = FALSE;
	float dc = 0;
	uint8_t mot_ref = 0;
	can_message_t empty_msg;
	empty_msg.id = EMPTY_ID;
	
	//Handling highscore timer
	uint8_t timer_enabled = FALSE;
	
	
		
	//Initializing receive message
	can_message_t receive_msg;
	receive_msg = *(CAN_create_message(&receive_msg,0,1,0));
	
	//Initializing gameover message
	can_message_t gameover_msg;
	CAN_create_message(&gameover_msg, GAMEOVER_DATA_ID,1, 0);
	
	


	while(1){
	
	//Reading messages from Node 1	
	CAN_recieve_data(&receive_msg);


	
	uint16_t ID = receive_msg.id;
	
	
	switch(ID) {
		
		case GAME_ID:
		
			//Starting highscore timer
			if(timer_enabled == FALSE) {
				TIMER_start(highscore_timer);
			}
			
			
			//Enable servo input from joystick
			dc = PWM_get_duty_cycle(receive_msg);
			PWM_set_duty_cycle(dc);
			
			
			//Enable solenoid input from right button
			if (receive_msg.data[SOLENOID_ENABLE]) {	
				receive_msg.data[SOLENOID_ENABLE] = 0;
				SOLENOID_enable();
				printf("SOLENOID_enabled\n");
				_delay_ms(150);
				SOLENOID_disable();
				
				
			}
			
			mot_ref = receive_msg.data[MOTOR_REF];
			MOTOR_position_control(mot_ref);
			
			//Game over condition
			if (IR_read() < IR_TRIGGER_VAL) { 
				
				TIMER_stop();
				for (uint8_t i = 0; i < 10; i = i+1) {
					CAN_send_message(&gameover_msg);
					_delay_ms(1);
				}
				//Clearing gameover state in Node 1
				CAN_send_message(&empty_msg);
			}
			
			break;
		
		
		case WIRELESS_ID:
		
			//Starting timer
			if(timer_enabled == FALSE) {
				TIMER_start(highscore_timer);
			}
			
				
			
			
			//Enabling wireless control
			while(1) { 
				
				HC05_set_control_input(); 
				
				//Game over condition
				if (IR_read() < IR_TRIGGER_VAL) {
					
					TIMER_stop();
					for (uint8_t i = 0; i < 10; i = i+1) {
						CAN_send_message(&gameover_msg);
						_delay_ms(1);
					}
					//Clearing gameover state in Node 1
					CAN_send_message(&empty_msg);
				}
					
			}
		
		}

	}

}

	
	
