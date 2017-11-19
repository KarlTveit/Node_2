/*
 * HC05.h
 *
 * Created: 16.11.2017 23:39:19
 *  Author: karlmt
 */ 


#ifndef HC05_H_
#define HC05_H_

#include <avr/interrupt.h>
#include "../CAN/CAN.h"
#include "../MOTOR/MOTOR.h"
#include "../SOLEDNOID/SOLENOID.h"
#include "../PWM/PWM.h"
#include "../MCP2515/MCP2515.h"


#define TX1_PIN 3


//App data
#define PLAY	1
#define RESET	2
#define QUIT	3
#define SHOOT	250

#define SERVO_LOWER_LIM		5
#define SERVO_UPPER_LIM		30

#define MOTOR_LOWER_LIM		50
#define MOTOR_UPPER_LIM		230



void HC05_init(unsigned int ubrr);
uint8_t HC05_receive(void);
uint8_t HC05_set_control_input(void);
uint8_t HC05_get_app_data(void);
uint8_t HC05_convert_to_motor_speed(uint8_t data);
uint8_t HC05_convert_to_motor_direction(uint8_t data);
double HC05_convert_to_servo_dc(uint8_t data);



#endif /* HC05_H_ */