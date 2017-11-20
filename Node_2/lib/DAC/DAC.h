/*
 * DAC.h
 *
 * Created: 08.11.2017 12:47:21
 *  Author: karlmt
 */ 


#ifndef DAC_H_
#define DAC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../DEFINITIONS.h"
#include "../TWI/TWI_Master.h"

void DAC_init(void);
void DAC_write(uint8_t data);



#endif /* DAC_H_ */