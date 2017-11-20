/*
 * HC_05.c
 *
 * Created: 16.11.2017 23:39:30
 *  Author: karlmt
 */ 

#include "HC05.h"

static /*volatile */uint8_t HC05_flag = 0;
/*volatile */uint8_t app_data = 0;

void HC05_init(unsigned int ubrr) {
	
	//Clearing baud rate register 
	UBRR1 = 0;
	
	//Setting TX pin as output
	DDRD |= (1 << TX1_PIN);
	
	//Setting output pin to low
	PORTD &= ~(1 << TX1_PIN);
	
	//Setting MSPI mode for operation and SPI data mode 0
	UCSR1C = (1<<UMSEL11)|(1<<UMSEL10)|(0<<UCSZ10)|(0<<UCPOL1);
	
	//Enable receiver and transmitter (must be done before setting the baud rate)
	UCSR1B = (1 << RXEN1)| (1 << TXEN1); 
	
	//Setting baud rate to 9600;
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	
	//Frame format: 8 bit data, 2 stop bit
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
	
	//Enable RX Complete Interrupt
	UCSR1B |= (1 << RXCIE1);

	//Global Interrupt Enable
	sei();
	
}


uint8_t HC05_receive(void) {
	
	//Waiting for message
	while( !(UCSR1A & (1 << RXC1)) ) {};
	
	HC05_flag = 1;
	
	return UDR1;
	
}



void HC05_set_control_input(void) {
	
	app_data = HC05_receive();
	
	if( app_data == PLAY || app_data == RESET ) {
		TIMER_start(highscore_timer);					
		//return 1;
	}
	
	
	if( app_data == SHOOT ) {
		SOLENOID_enable();
		printf("SOLENOID_enabled\n");
		_delay_ms(50);
		SOLENOID_disable();
	}
	else if( app_data > SERVO_LOWER_LIM && app_data < SERVO_UPPER_LIM ) {
		PWM_set_duty_cycle(app_data);
		//return 0;
	}
	else if(app_data > MOTOR_LOWER_LIM && app_data < MOTOR_UPPER_LIM ) {
		//printf("nå skal jeg styre motoren :) \n\n");
		MOTOR_write(HC05_convert_to_motor_speed(app_data), HC05_convert_to_motor_direction(app_data));
		//return 0;
	}
	

}

uint8_t HC05_get_app_data(void) {
	return app_data;
}

uint8_t HC05_convert_to_motor_speed(uint8_t data) {
	uint8_t speed = (uint8_t)((abs(data-50-90))/0.71);
	if (abs(data-50-90) < 15) {
		speed = 0;
	}
	return speed*1.8;
}

uint8_t HC05_convert_to_motor_direction(uint8_t data) {
	
	return (data > 130) ? RIGHT:LEFT;
}

double HC05_convert_to_servo_dc(uint8_t data) {
	printf("SERVO INPUT: %d\n\n",(((data*10)-5)/250)*(31-16) + 15);
	return (double)(((data*10)-5)/250)*(31-16) + 15;
}



ISR(USART1_RX_vect) {
	
	//Set interrupt flag
	HC05_flag = 0;
	
	//Get data from app controller
	app_data = UDR1;
	
	//Clear interrupt
	UCSR1A &= ~(1 << RXCIE1);
	
}

