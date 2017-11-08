/*
 * MOTOR.c
 *
 * Created: 08.11.2017 10:37:44
 *  Author: karlmt
 */ 


#include "MOTOR.h"

/*
max = -8284
min = */

void MOTOR_init(void) {
	//Setting output-pins:
	DDRH |= (1<<DDH1)
	|  (1<<DDH3)
	|  (1<<DDH4)
	|  (1<<DDH5)
	|  (1<<DDH6);
	TWI_Master_Initialise();
	PORTH |= (1<<EN)		//Enable motor
		  |  (1<<DIR);		//Motor direction
	PORTH &=  ~(1<<_RST);		//Counter reset
	PORTH |=  (1<<_RST);
	PORTH &= ~(1<<_OE);		//Allowing the counter to appear on MJ2
	PORTH &= ~(1<<SEL);		//Selecting high byte (MSB)
	
	
	
	
}



uint16_t MOTOR_read(void) {
	
	PORTH &= ~(1<<_OE);		//Allowing the counter to appear on MJ2
	PORTH &= ~(1<<SEL);		//Selecting high byte (MSB)
	
	
	_delay_us(25);
	
	uint8_t msb = PINK;
	PORTH |= (1<<SEL);		//Selecting low byte (LSB)
	
	_delay_us(25);
	
	uint8_t lsb = PINK;
	PORTH &= ~(1<<_RST);
	PORTH |=  (1<<_RST);
	PORTH |= (1<<_OE);
	
	return (msb << 8) | lsb;
	
}


void MOTOR_write(uint8_t speed, uint8_t direction) {
	
	if (direction == RIGHT) {
		PORTH |= (1<<PH1);
	}
	else {
		PORTH &= ~(1<<PH1);
	}
	DAC_write(speed);
}





/*

void MOTOR_write(uint8_t pos, uint8_t direction) {
	
	uint8_t curr_pos = MOTOR_read()
	
	if (direction == RIGHT) {
		PORTH |= (1<<PH1);
	}
	else {
		PORTH &= ~(1<<PH1);
	}
	DAC_write(speed);
}*/

uint8_t MOTOR_get_speed(void){

	can_message_t *msg;
	CAN_recieve_data(msg);
	
	int8_t pos = msg->data[0]-127;
	uint8_t speed = (abs(pos)*0.7);
	/*if (pos < 0) {
		speed = -pos;
	}*/
	return speed;
};

uint8_t MOTOR_get_direction(void) {

	can_message_t *msg;
	CAN_recieve_data(msg);	
	
	if (msg->data[0] > 127) {
		return RIGHT;
	}
	return LEFT;
	
}
	
