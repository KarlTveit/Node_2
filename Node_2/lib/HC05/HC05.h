/*
 * HC05.h
 *
 * Created: 16.11.2017 23:39:19
 *  Author: karlmt
 */ 


#ifndef HC05_H_
#define HC05_H_

#include <avr/interrupt.h>
#include <stdlib.h>

#include "../CAN/CAN.h"
#include "../MOTOR/MOTOR.h"
#include "../SOLEDNOID/SOLENOID.h"
#include "../PWM/PWM.h"
#include "../MCP2515/MCP2515.h"
#include "../TIMER/TIMER.h"
#include "../DEFINITIONS.h"


void HC05_init(unsigned int ubrr);
uint8_t HC05_receive(void);
void HC05_set_control_input(void);
uint8_t HC05_get_app_data(void);
uint8_t HC05_convert_to_motor_speed(uint8_t data);
uint8_t HC05_convert_to_motor_direction(uint8_t data);
double HC05_convert_to_servo_dc(uint8_t data);



#endif /* HC05_H_ */