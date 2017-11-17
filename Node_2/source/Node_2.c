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
#include "../lib/TIMER/TIMER.h"
#include "../lib/SOLEDNOID/SOLENOID.h"
#include "../lib/CAN_DEFINES/CAN_DEFINES.h"
#include "../lib/HC05/HC05.h"
uint8_t RECEIVED = 0;


ISR(BADISR_vect)
{
	printf("Trist\n");
}

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
	
	
	
	cli();	//disable alle interrupts
	
	DDRA = 0xFF;
	UART_Init(UBRR);
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
	PID_init();
	printf("etter inits");

	
	/*can_message_t gameover_msg;
	gameover_msg.id = GAMEOVER_DATA_ID;
	gameover_msg.length = 1;
	gameover_msg.data[0] = FALSE;
	
	uint8_t count = 0;*/
	
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

/*
		while (1)
		{	
			//printf("PWM CONVERT: %d\n\n", (uint8_t)(((17*10)-5)/250)*(31-16) + 16);
			HC05_receive();
			printf("App_data = %d\n\n", HC05_get_app_data());
			
			
			HC05_set_control_input();
			
		}
*/
	//SOLENOID_disable();
		while(1){
		//_delay_ms(100);
		
		//printf("ADC IR %d\n",IR_read());
	
		printf("Hello");
		can_message_t msg; 
		msg.id = 0;
		msg.length = 1;
		msg.data[0] = 0;

		//msg.data[GAME_ENABLE] = 0;	//--> clearing bit in order to recognize new message
		
		CAN_recieve_data(&msg);
		_delay_ms(10);
		
		
		//printf("IN MAIN:\n");
		//if (msg.id == 100 && msg.length == 7){	
			CAN_print_message(msg);
		//}
		
		if (msg.id == GAME_ID /*&& msg.data[GAME_ENABLE]*/ && msg.length == 7) {
			
				//MOTOR_write_pos(PID_control(msg));
				PID_update_ref(msg.data[2]);
			
			float dc = PWM_get_duty_cycle(msg);
			PWM_set_duty_cycle(dc);
		
			printf("In the if");
		
			
			
		
		
			
				if (/*msg.id == GAME_ID &&*/ msg.data[SOLENOID_ENABLE]) {
				
					SOLENOID_enable();
					printf("SOLENOID_enabled\n");
					_delay_ms(300);
					SOLENOID_disable();

					//_delay_ms(1000);
				}
		
					//uint8_t target_pos = msg.data[MOTOR_REF];
					MOTOR_write_pos(PID_control(msg));
			
					//MOTOR_write_speed(MOTOR_get_speed(msg),MOTOR_get_direction(msg));
					//printf("Motor speed: %d\nMotor dir: %d\n", MOTOR_get_speed(msg),MOTOR_get_direction(msg));
			
	
		
		
		
		
		
				/*if (IR_read() < 15) {
					printf("Sending gameover message \n\n");
					gameover_msg.data[TIMER_VAL] = TIMER_get_time();
			
					CAN_send_message(&gameover_msg);
					_delay_ms(1);
					CAN_print_message(gameover_msg); 

				}
		*/
	
		
		
				//MCP_CANINTF = MCP_CANINTF | 0b00000001;
	}
	}
	printf("OUTTA WHILE");
}