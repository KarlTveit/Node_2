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
uint8_t RECEIVED = 0;


/*
ISR(BADISR_vect)
{
	printf("Trist\n");
}*/

//
//ISR(USART0_RX_vect)
//{
	//printf("uart interrupt\n");
	//RECEIVED = 1;
	//
	//unsigned char temp = UDR0;
	//UART_Transmit(temp); // for å teste at det funker
//}


int main(void) {
	
	//cli();	//disable alle interrupts
	
	DDRA = 0xFF;
	UART_init(UBRR);
	HC05_init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	CAN_init();
	PWM_init();
	DAC_init();
	
	//Enable global interrupt
	//sei();
	
	
	MOTOR_init();
	IR_init();
	SOLENOID_init();
	TIMER_init();
	
	//PID_init();

	//Initializing variables
	uint8_t game_enable = FALSE;
	float dc = 0;
	uint8_t mot_ref = 0;
	
	
	//Handling highscore timer
	uint8_t timer_enabled = FALSE;
	
	
		
	//Initializing receive message
	can_message_t receive_msg;
	CAN_create_message(&receive_msg,0,1,0);
	
	//Initializing gameover message
	can_message_t gameover_msg;
	CAN_create_message(&gameover_msg, GAMEOVER_DATA_ID,1, 0);
	

	while(1){

	//Reading messages from Node 1	

	
	can_message_t receive_msg;
	receive_msg.id = 0;
	receive_msg.length = 1;
	receive_msg.data[0] = 0;
	CAN_recieve_data(&receive_msg);
	_delay_ms(10);
	//CAN_print_message(receive_msg);
	
	printf("right slider: %d\n", receive_msg.data[2]);
	
	
	
	/*	
	while (/ *MOTOR_scale_to_8bit(MOTOR_read()) > (receive_msg.data[2]) || MOTOR_scale_to_8bit(MOTOR_read()) < (receive_msg.data[2]- PID_control(receive_msg))* /1) {
		if (MOTOR_read() > 0 || MOTOR_read() < -9000) {
			MOTOR_write(0,RIGHT);
		}*/
		/*
	while(1) {
	
		uint8_t target = receive_msg.data[2];
		
		if (PID_get_flag == 1) {
			target = target - PID_control(receive_msg);
		}
		
		if (MOTOR_scale_to_8bit(MOTOR_read()) < (receive_msg.data[2]- PID_control(receive_msg))) {
			MOTOR_write(127*((receive_msg.data[2]-MOTOR_scale_to_8bit(MOTOR_read()))/255),RIGHT);
		}
		else if (MOTOR_scale_to_8bit(MOTOR_read()) > (receive_msg.data[2]- PID_control(receive_msg))) {
			MOTOR_write(127*((receive_msg.data[2]-MOTOR_scale_to_8bit(MOTOR_read()))/255),LEFT);
		}
		else {
			MOTOR_write(0,RIGHT);
		}
	}*/
/*
	while(1) {
		
		if (IR_read() < 15) {
			printf("Sending gameover message \n\n");
			gameover_msg.data[TIMER_VAL] = 1;/ *TIMER_get_time();* /
		
			CAN_send_message(&gameover_msg);
			_delay_ms(1);
			CAN_print_message(gameover_msg);

		}
		else {
			gameover_msg.data[TIMER_VAL] = 0;
			CAN_send_message(&gameover_msg);
		}
	}
		*/
	
	
	uint16_t ID = receive_msg.id;
	
	
	switch(ID) {
		
		case GAME_ID:
		
			//Handling timer
			if(timer_enabled == FALSE) {
				TIMER_start(highscore_timer);
			}
			
			
			//Enable servo, input from joystick ENDRE DETTE????????????????????????????????????????????????????????   ?????????????????????  ????????????????????
			dc = PWM_get_duty_cycle(receive_msg);
			PWM_set_duty_cycle(dc);
			
			
			//Enable solenoid, input from right button
			if (receive_msg.data[SOLENOID_ENABLE]) {	
				
				SOLENOID_enable();
				printf("SOLENOID_enabled\n");
				_delay_ms(100);
				SOLENOID_disable();
				
			}
			
			mot_ref = receive_msg.data[MOTOR_REF];
			
			MOTOR_position_control(mot_ref);
			
			if (IR_read() < 15) {
				printf("IR_read() = %d \n", IR_read()); 
				TIMER_stop();
				printf("Sending gameover message \n\n");
				gameover_msg.data[TIMER_VAL] = TIMER_get_time();
				
				
				CAN_send_message(&gameover_msg);
				_delay_ms(1);
				CAN_print_message(gameover_msg);

			}
			
			
			break;
		
		
		case WIRELESS_ID:
		
			//Handling timer
			if(timer_enabled == FALSE) {
				TIMER_start(highscore_timer);
			}
			
			
			//Must press play to enable game
			if (HC05_receive() == PLAY) {
				
				game_enable = TRUE;
				
			}
			
			
			//Enabling wireless controller
			while(game_enable) { 
				HC05_set_control_input(); 
				
				if (IR_read() < 15) {
					
					TIMER_stop();
					game_enable = FALSE;
					
					gameover_msg.data[TIMER_VAL] = TIMER_get_time();
					
					CAN_send_message(&gameover_msg);
					_delay_ms(1);
					CAN_print_message(gameover_msg);

				}
					
			}
			
			
			
		
	}
	
	
	/*	
	if (msg.id == GAME_ID / *&& msg.data[GAME_ENABLE]* / && msg.length == 7) {
			
			//MOTOR_position_control(PID_control(msg));
			//PID_update_ref(msg.data[2]);
			
		float dc = PWM_get_duty_cycle(msg);
		PWM_set_duty_cycle(dc);
		
		//printf("In the if");
		
			
			
		
		
			
			if (/ *msg.id == GAME_ID &&* / msg.data[SOLENOID_ENABLE]) {
				
				SOLENOID_enable();
				printf("SOLENOID_enabled\n");
				_delay_ms(300);
				SOLENOID_disable();

				//_delay_ms(1000);
			}
		
				//uint8_t target_pos = msg.data[MOTOR_REF];
				printf("msg.data[2] = %d\n", msg.data[2]);
					
				printf("PID_control(msg) = %d\n\n", PID_control(msg));
					
				MOTOR_position_control(msg.data[2] / *- PID_control(msg)* /);
			
				//MOTOR_write(MOTOR_get_speed(msg),MOTOR_get_direction(msg));
				//printf("Motor speed: %d\nMotor dir: %d\n", MOTOR_get_speed(msg),MOTOR_get_direction(msg));
			
	
		
		
		
		
		
			/ *if (IR_read() < 15) {
				printf("Sending gameover message \n\n");
				gameover_msg.data[TIMER_VAL] = TIMER_get_time();
			
				CAN_send_message(&gameover_msg);
				_delay_ms(1);
				CAN_print_message(gameover_msg); 

			}
	* /
	
		
		
				//MCP_CANINTF = MCP_CANINTF | 0b00000001;
	}
	else if (msg.id == WIRELESS_ID) {
		uint8_t enable = FALSE;
		if (HC05_receive() == PLAY) {
			enable = TRUE;
			TIMER_start(highscore_timer);
		}
		
		while(enable) {
			HC05_set_control_input();
		}
		
	/ *	static uint8_t game_enable = FALSE;
		
		if (HC05_receive() == PLAY) {
			game_enable = TRUE;
			TIMER_start(highscore_timer);
		}
		
		
		while (game_enable) {
			HC05_set_control_input();
			
			
			if (IR_read() < 15) {
				printf("Sending gameover message \n\n");
				gameover_msg.data[0] = TRUE;
				
				CAN_send_message(&gameover_msg);
				_delay_ms(1);
				CAN_print_message(gameover_msg);
				
				game_enable = FALSE;

			}
		}* /
			
		
	}*/
	}
	printf("OUTTA WHILE");
		//_delay_ms(100);
		
	//printf("ADC IR %d\n",IR_read());
	
/*	printf("Hello");
	can_message_t msg; 
	msg.id = 0;
	msg.length = 1;
	msg.data[0] = 0;*/

	//msg.data[GAME_ENABLE] = 0;	//--> clearing bit in order to recognize new message
}

	
	
	/*

	can_message_t msg;
	msg.id = 0;
	msg.length = 1;
	msg.data[0] = 0;

	//msg.data[GAME_ENABLE] = 0;	//--> clearing bit in order to recognize new message
		
	CAN_recieve_data(&msg);
	_delay_ms(10);*/

	
	/*while (MOTOR_scale_to_8bit(MOTOR_read()) > (msg.data[2]) || MOTOR_scale_to_8bit(MOTOR_read()) < (msg.data[2]- PID_control(msg))) {
		/ *if (MOTOR_read() > 0 || MOTOR_read() < -9000) {
			MOTOR_write(0,RIGHT);
		}
		
		else* / 
		uint8_t target = msg.data[2];
		
		if (PID_get_flag == 1) {
			target = target - PID_control(msg);
		}
		
		if (MOTOR_scale_to_8bit(MOTOR_read()) < (msg.data[2]- PID_control(msg))) {
			MOTOR_write(127*((msg.data[2]-MOTOR_scale_to_8bit(MOTOR_read()))/255),RIGHT);
		}
		else if (MOTOR_scale_to_8bit(MOTOR_read()) > (msg.data[2]- PID_control(msg))) {
			MOTOR_write(127*((msg.data[2]-MOTOR_scale_to_8bit(MOTOR_read()))/255),LEFT);
		}
		else {
			MOTOR_write(0,RIGHT);
		}
	}
*/



/*
	gameover_msg.id = GAMEOVER_DATA_ID;
	gameover_msg.length = 1;
	gameover_msg.data[0] = FALSE;*/

	
	
	
/*
	while(1){
		TIMER_start();
		_delay_ms(3000);
		TIMER_stop();
		printf("time = %d\n\n", TIMER_get_time());
		
		gameover_msg.data[TIMER_VAL] = TIMER_get_time();
		
		//CAN_send_message(&gameover_msg);
		CAN_print_message(gameover_msg);
		printf("\n\n");

	}
	*/

		/*while (1)
		{	
			//printf("PWM CONVERT: %d\n\n", (uint8_t)(((17*10)-5)/250)*(31-16) + 16);
			/ *HC05_receive();* /
			
			
			
			HC05_set_control_input();
			
		}*/

	//SOLENOID_disable();