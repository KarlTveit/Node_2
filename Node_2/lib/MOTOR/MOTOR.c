/*
 * MOTOR.c
 *
 * Created: 08.11.2017 10:37:44
 *  Author: karlmt
 */ 
#include <stdio.h>
#include <stdlib.h>
#include "MOTOR.h"
#include "../DAC/DAC.h"

volatile int16_t rot_max = 0;
volatile int16_t rot_min = 0;


void MOTOR_init(void) {
	
	//Setting output-pins:
	DDRH |= (1 << DDH1) | (1 << DDH3) | (1 << DDH4) | (1 << DDH5) | (1 << DDH6); 
	
	TWI_Master_Initialise();
	
	//Enable motor
	PORTH |= (1 << EN);
	
	//Motor direction
	PORTH |= (1 << DIR);		
	
	//Counter reset		
	PORTH &=  ~(1 << _RST);		
	PORTH |=  (1 << _RST);
	
	//Allowing the counter to appear on MJ2
	PORTH &= ~(1 << _OE);	
	
	//Selecting high byte (MSB)	
	PORTH &= ~(1 << SEL);
	
	//Setting rot_min
	MOTOR_write(127,LEFT);
	_delay_ms(600);
	MOTOR_write(0,LEFT);
	
	//Resetting the encoder so that encoder value = 0
	while (MOTOR_read()!= 0){ 
		
		_delay_ms(20);
		PORTH &= ~(1<<_RST);
		_delay_ms(20);
		PORTH |=  (1<<_RST);
		
	}
	
	rot_min = MOTOR_read();
	_delay_ms(1000);
	
	
	//Setting rot_max
	MOTOR_write(127,RIGHT);
	_delay_ms(600);
	MOTOR_write(0,RIGHT);

	rot_max = MOTOR_read();
	_delay_ms(1000);
	
	
	//Initial position in center
	MOTOR_write(127,LEFT);
	_delay_ms(300);
	MOTOR_write(0,LEFT);		

}



 void MOTOR_encoder_reset(void){ 
	 
	 //Allowing the counter to appear on MJ2
	PORTH &= ~(1 << _OE);	
	
	//Selecting high byte (MSB)	
	PORTH &= ~(1 << SEL);		
	_delay_us(25);
	
	uint8_t msb = PINK;
	
	//Selecting low byte (LSB)
	PORTH |= (1 << SEL);		
	_delay_us(25);
	
	uint8_t lsb = PINK;
	
	//Counter reset	
	PORTH &= ~(1 << _RST);
	_delay_ms(20);
	PORTH |=  (1 << _RST);
	
	//Denying the counter to appear on MJ2
	PORTH |= (1<<_OE);
	 
 }
 


uint16_t MOTOR_read(void) {
	
	PORTH &= ~(1 << _OE);	
	
	//Selecting high byte (MSB)	
	PORTH &= ~(1 << SEL);		
	_delay_us(25);
	
	uint8_t msb = PINK;
	
	//Selecting low byte (LSB)
	PORTH |= (1 << SEL);		
	_delay_us(25);
	
	uint8_t lsb = PINK;

	PORTH |= (1 << _OE);
	
	//Returning 16 bit
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


//P controlled 
void MOTOR_position_control(int16_t target_pos) {

		
		uint8_t current_pos = MOTOR_scale_to_8bit(MOTOR_read()); 
		//Proportional regulation from feedback
		uint8_t speed = abs(target_pos-current_pos)*1;
		
		//Saturation
		if (speed > 120) {
			speed = 120;
		}
		else if (speed < 60 && speed > 30) {
			speed = 60;
		}
		
		
		if (target_pos/*+10 */> current_pos) {
		
			MOTOR_write(speed,RIGHT);
		
		}
	
		else if (target_pos/*-10*/ < current_pos) {
			
			MOTOR_write(speed,LEFT);
			
		}
		else {
			MOTOR_write(0,RIGHT);
			
		}
	
	
	 }





uint8_t MOTOR_scale_to_8bit(int16_t encoder_val) {
	
	if (encoder_val < rot_max) {
		encoder_val = rot_max;
	}
	else if (encoder_val > rot_min) {
		encoder_val = rot_min;
	}
	
	uint8_t val = -(encoder_val *(255.0/rot_max));
	
	return 255-val;
}

