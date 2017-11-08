/*
 * PID.h
 *
 * Created: 08.11.2017 14:55:59
 *  Author: karlmt
 */ 



#ifndef PID_H_
#define PID_H_

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../DAC/DAC.h"
#include "../MOTOR/MOTOR.h"

#define F_CPU 16000000

void PID_init(void);
uint8_t PID_scale(int8_t motor_rot);


#endif /* PID_H_ */