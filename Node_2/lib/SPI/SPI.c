/*
 * SPI.c
 *
 * Created: 04.10.2017 09:03:00
 *  Author: tonjaj
 */ 


#include "SPI.h"



void SPI_init() {
	
	

	DDRB |= (1<<DDB1);						//SCK
	DDRB |= (1<<DDB2);						//MOSI
	DDRB |= (1<<DDB7);
	DDRB |= (1<<DDB0);						//SS
	DDRB &= ~(1<<DDB3);						//MISO
	
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);					//Master mode enable;						//SPI Enable
		
	//SPCR &= ~(1<<DORD);						//MSB of data word transmitted first
	
	
	//SPCR |= (1<<SPR0);						//SCK frequency = F_OSC/16 
	//SPCR &= ~(1<<SPR1);
	
	//SPI_disable_chipselect();
	//printf("SPI_init complete \n");
	
	
}



void SPI_send(uint8_t message) {
	
	SPDR = message;							//Start transmission
	//printf("SPI_send \n");
	
	while (!(SPSR & (1<<SPIF))){
		//printf("stuck\n");
	}			//Wait until transmission is complete
}



uint8_t SPI_read() {
	
	SPI_send(0x01);							//Transmisson of dummy byte, to be able to read from slave
	
	//while (!(SPSR & (1<<SPIF))) {}			//Wait until transmission is complete
	
	return SPDR;							//All messages will end with the dummy byte????
	
}


void SPI_enable_chipselect(void) { // 1 --> enable
	PORTB &= ~(1<<PB7);
}



void SPI_disable_chipselect(void) { // 1 --> enable
	PORTB |= (1<<PB7);
}