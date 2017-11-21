#include "UART.h"




void UART_init(unsigned int ubrr) {
	
	// Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); 
	
	// Set frame format: 8data, 2 stop bit
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

	
	//RX Complete Interrupt Enable
	UCSR0B |= (1 << RXCIE0);
	
	//Receive Complete Flag Enable
	UCSR0A |= (1 << RXC0);
	
	//Global Interrupt Flag Enable
	sei();

}


void UART_Transmit(unsigned char data) {
	
	while (!(UCSR0A & (1<<UDRE0) )){}
	
	UDR0 = data;
/*	return 3;*/
};



unsigned char UART_Recieve(void) {
	
	while ( !(UCSR0A & (1<<RXC0)));
	
	return UDR0;
	
};