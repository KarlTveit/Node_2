/*
 * IR.h
 *
 * Created: 01.11.2017 09:59:19
 *  Author: karlmt
 */ 

#ifndef IR_H_
#define IR_H_

#include <avr/io.h>
#include "../CAN/CAN.h"
#include "../DEFINITIONS.h"

uint8_t IR_read(void);
void IR_init(void);


#endif /* IR_H_ */