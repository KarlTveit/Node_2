/*
 * CAN.h
 *
 * Created: 04.10.2017 09:05:37
 *  Author: tonjaj
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "../MCP2515/MCP2515.h"
#include "../DEFINITIONS.h"


typedef struct {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
}can_message_t;


void CAN_init(void);
void CAN_send_message(can_message_t *message);
void CAN_recieve_data(can_message_t *message);
void CAN_print_message(can_message_t message);
can_message_t* CAN_create_message(can_message_t* message, uint16_t id, uint8_t length, uint8_t data[]);




#endif /* CAN_H_ */