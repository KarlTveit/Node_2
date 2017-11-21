/*
 * DEFINITIONS.h
 *
 * Created: 19.11.2017 05:36:28
 *  Author: karlmt
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


#define CLOCKS_PER_SEC			1000000


#define TRUE					1
#define FALSE					0
#define NULL_PTR				(void*)0


#define TIMER_VAL				0


//CAN message IDs
#define		GAME_ID				100
#define		GAMEOVER_DATA_ID	90
#define		WIRELESS_ID			80



//Game message indexes
#define		SERVO_REF			0
#define		MOTOR_REF			2	
#define		SOLENOID_ENABLE		3
#define		GAME_ENABLE			7

//JOY
#define		RIGHT_BUTTON		0b00000001
#define		LEFT_BUTTON			0b00000010
#define		JOY_BUTTON			0b00000100


//SPI 
#define		DD_SS				DDB4
#define		DD_MOSI				DDB5
#define		DD_MISO				DDB6
#define		DD_SCK				DDB7
#define		DDR_SPI				DDRB


//SRAM
#define		SRAM_START_ADDRESS 1800


//Application data
#define		PLAY	1
#define		RESET	2
#define		QUIT	3
#define		SHOOT	250

#define		SERVO_LOWER_LIM		5
#define		SERVO_UPPER_LIM		30

#define		MOTOR_LOWER_LIM		50
#define		MOTOR_UPPER_LIM		230


//Motor
#define		LEFT	0
#define		RIGHT	1

//DAC
#define MAX520_ADDR		0b01011110

//PWM
#define		PWM_min		14
#define		PWM_max		30


//HC-05
#define TX1_PIN 3

//App data
#define PLAY	1
#define RESET	2
#define QUIT	3
#define SHOOT	250

#define SERVO_LOWER_LIM		5
#define SERVO_UPPER_LIM		30

#define MOTOR_LOWER_LIM		50
#define MOTOR_UPPER_LIM		230

//Output and input
#define OUTPUT_ENABLE_ALL 0xFF

//IR
#define IR_TRIGGER_VAL 15

#endif /* DEFINITIONS_H_ */