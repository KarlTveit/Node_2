/*
 * MOTOR.c
 *
 * Created: 08.11.2017 10:37:44
 *  Author: karlmt
 */ 

#include <stdlib.h>
#include "MOTOR.h"
#include "../DAC/DAC.h"
/*
max = -8284
min = */


static int16_t rot_max = 0;
static int16_t rot_min = 0;


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
	//PORTH &= ~(1<<_RST);
	//PORTH |=  (1<<_RST);
	PORTH |= (1<<_OE);
	
	return (msb << 8) | lsb;
	
}


void MOTOR_write_speed(uint8_t speed, uint8_t direction) {
	
	if (direction == RIGHT) {
		PORTH |= (1<<PH1);
	}
	else {
		PORTH &= ~(1<<PH1);
	}
	DAC_write(speed);
}



void MOTOR_write_pos(uint8_t target_pos) {
	
	uint8_t current_pos = PID_scale(MOTOR_read());
	printf("target pos = %d\n current pos = %d\n motor read = %d\n rotmax%d\n rotmin%d\n" ,target_pos,current_pos,MOTOR_read()),rot_max,rot_min;
	if (target_pos > current_pos) {
		PORTH |= (1<<PH1);
		while (target_pos > PID_scale(MOTOR_read())) {
			DAC_write(127);
		}
	}
	else if (target_pos < current_pos){
		PORTH &= ~(1<<PH1);
		while (target_pos < PID_scale(MOTOR_read())) {
			DAC_write(127);
		}
	}
	
}




uint8_t MOTOR_get_speed(can_message_t msg){

	/*can_message_t msg;
	CAN_recieve_data(&msg);*/
	
	int8_t pos = msg.data[MOTOR_REF]-127;
	uint8_t speed = (abs(pos)) /*+ PID_control()*/;
	/*if (pos < 0) {
		speed = -pos;
	}*/
	
	
	return speed;
};

uint8_t MOTOR_get_direction(can_message_t msg) {

/*
	can_message_t msg;
	CAN_recieve_data(&msg);	*/
	
	if (msg.data[MOTOR_REF] > 127) {
		return RIGHT;
	}
	return LEFT;
	
}


/*
uint8_t MOTOR_scale(int8_t encoder_val) {
	return (uint8_t)((encoder_val-rot_min)/(rot_max-rot_min))*255;
}
	*/
