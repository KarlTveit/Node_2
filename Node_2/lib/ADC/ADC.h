

#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "stdio.h"
#include "stdlib.h"

#include "../UART/UART.h"
#include "../DEFINITIONS.h"

#define ext_ram         ((volatile char*) 0x1800)
#define ext_ram_size    0x800
#define ext_adc         ((volatile char*) 0x1400)


typedef enum{
	
	joyY = 0x4,
	joyX = 0x5,
	IR = 0x3,
	right_slider = 0x6,
	left_slider = 0x7
	
} channel;


uint8_t ADC_read(channel ch);
void ADC_init(void);



#endif /* ADC_H_ */