/*
 * Node_2.c
 *
 * Created: 18.10.2017 15:14:10
 *  Author: karlmt
 */ 



#define F_CPU 16000000UL  // clock frequency in Hz

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

uint8_t RECEIVED = 0;

ISR(USART0_RXC_vect)
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
	
	
	printf("hello\n");
	CAN_init();
/*
	can_message_t m;
	m.id = 3;
	m.length = 1;
	m.data[0] = (uint8_t) 'H';*/
	//CAN_send_message(&m);
	
	
	
	PWM_init();
	
	
	while(1){
	
	/*can_message_t msg;
	if(MCP2515_read(MCP_CANINTF) & 1){
		CAN_recieve_data(&msg);
		CAN_print_message(msg);
		MCP2515_bit_modify(MCP_CANINTF,0x1,0x1);*/
		
		float dc = PWM_get_duty_cycle();
		printf("dc = %d\n", dc);
		PWM_set_duty_cycle(dc);	
		
		
		
		//MCP_CANINTF = MCP_CANINTF | 0b00000001;
	
	}
	
}