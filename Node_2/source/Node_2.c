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
#include "../lib/JOY/JOY.h"
#include "../lib/SRAM/SRAM.h"
#include "../lib/OLED/OLED.h"
#include "../lib/MENU/MENU.h"
#include "../lib/SPI/SPI.h"
#include "../lib/MCP2515/MCP2515.h"
#include "../lib/CAN/CAN.h"
#include "../lib/IR/IR.h"
#include "../lib/DAC/DAC.h"
#include "../lib/TWI/TWI_Master.h"
#include "../lib/PID/PID.h"
#include "../lib/SOLEDNOID/SOLENOID.h"
#include "../lib/CAN_DEFINES/CAN_DEFINES.h"
uint8_t RECEIVED = 0;




ISR(USART0_RX_vect)
{
	RECEIVED = 1;
	
	unsigned char temp = UDR0;
	UART_Transmit(temp); // for å teste at det funker
}


int main(void) {
	
	
	//disable alle interrupts
	cli();
	
	DDRA = 0xFF;
	UART_Init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	//init_SRAM();
	
	
	CAN_init();
	PWM_init();
	DAC_init();
	MOTOR_init();
	IR_init();
	SOLENOID_init();
	TIMER_init();
	//PID_init();
	/*while(1) {
		PID_init();
	}*/
	
	
	/*while (1)
	{
		TIMER_start();
		_delay_ms(4000);
		TIMER_stop();
		printf("time = %d\n\n", TIMER_get_time());
	}*/
	
	
	can_message_t gameover_msg;
	gameover_msg.id = GAMEOVER_DATA_ID;
	gameover_msg.length = 1;
	
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
	
		while(1){
		_delay_ms(100);
		
		//printf( "\n\nSolenoid pin = %d\n\n", PINB & (1 << PB4));
		
		//printf("ADC IR %d\n",IR_read());
	/*can_message_t msg;
	if(MCP2515_read(MCP_CANINTF) & 1){
		CAN_recieve_data(&msg);
		CAN_print_message(msg);
		MCP2515_bit_modify(MCP_CANINTF,0x1,0x1);*/

		can_message_t msg;
		CAN_recieve_data(&msg);
		//_delay_ms(100);
		//printf("IN MAIN:\n");
		CAN_print_message(msg);
		
		while (msg.id == GAME_ID /*&& msg.data[GAME_ENABLE]*/) {
			CAN_recieve_data(&msg);
			//if (msg.id == 100) {
				printf("msg.id == GAME_ID && msg.data[GAME_ENABLE]");
				CAN_print_message(msg);
				float dc = PWM_get_duty_cycle(msg);
				PWM_set_duty_cycle(dc);
			//}
			//float dc = PWM_get_duty_cycle(msg);
			//printf("dc = %d\n", dc);
			
			//printf("Motor speed: %d\nMotor dir: %d\n", MOTOR_get_speed(msg),MOTOR_get_direction(msg));
			
		if (/*msg.id == GAME_ID && */msg.data[SOLENOID_ENABLE]) {
				
				SOLENOID_enable();
				//printf("SOLENOID_enabled\n");
				_delay_ms(50);
				SOLENOID_disable();

				//_delay_ms(1000);
			}
			//printf("msg data 2 = %d\n", msg.data[2]);
			uint8_t target_pos = msg.data[MOTOR_REF];
			//MOTOR_write_pos(target_pos - PID_control(msg));
			
			MOTOR_write_speed(MOTOR_get_speed(msg),MOTOR_get_direction(msg));
			
			
		//}
		
		
		
	/*	can_message_t gameover_msg;
		gameover_msg.id = GAMEOVER_DATA_ID;
		gameover_msg.length = 1;
		
		if (*){
			printf("Sending gameover message \n\n");
			gameover_msg.data[TIMER_VAL] = TIMER_get_time();
			
			CAN_send_message(&gameover_msg);
			CAN_print_message(gameover_msg); 

		}*/
		
	}
		
		
		//MCP_CANINTF = MCP_CANINTF | 0b00000001;
	}
}