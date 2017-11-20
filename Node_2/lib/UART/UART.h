#include <avr/io.h>
#include <avr/interrupt.h>
#include "../DEFINITIONS.h"

void UART_init(unsigned int ubrr);
void UART_Transmit(unsigned char data);
unsigned char UART_Recieve(void);