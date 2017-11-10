/*
 * PWM.h
 *
 * Created: 25.10.2017 10:07:21
 *  Author: Administrator
 */ 

#include <avr/io.h>
#ifndef PWM_H_
#define PWM_H_

#define PWM_min 15.6-1.7
#define PWM_mid	23.4-1.7
#define PWM_max 31.2-1.7


void PWM_init(void);

float PWM_get_duty_cycle(void);

void PWM_set_duty_cycle(float val);


#endif /* PWM_H_ */