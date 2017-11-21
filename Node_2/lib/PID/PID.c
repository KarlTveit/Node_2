/*
* PID.c
*
* Created: 08.11.2017 14:55:41
*  Author: karlmt
*/
#include "PID.h"

#include <stdlib.h>
volatile int16_t rot_max = 0;
volatile int16_t rot_min = 0;

//double motor_mid = 0;
double Kp = 1;
double Ki = 1;
double Kd = 0.1;
double dt = 1/25;
double integral = 0;
int8_t error_integrated = 0;
int16_t prev_error = 0;
volatile int16_t dir = LEFT;
static uint8_t step_size = 0;
int16_t ref_position = 0;
static volatile pid_flag = 0;
//static uint8_t right_ref = 255;
//static uint8_t left_ref = 0;
//static uint8_t mid_ref = 127;
//static uint8_t scaling_factor = 1;


ISR(TIMER2_OVF_vect) {
	
	pid_flag = 1;
	//printf("WTFF");	
	//int16_t ref = ref_position;
	//
	//uint8_t ref = msg->data[0];
	//uint8_t measured = PID_scale(MOTOR_read());
	//
	//error = ref - measured;
	//
	//integral += error*dt;
	//double derivative = -(error - prev_error)/dt;
	//prev_error = error; 
	//double gain =  Kp * error + Ki * integral + Kd * derivative;
	//
	//uint8_t dir;
	//
	//if (error > 0) {
		//dir = RIGHT;
	//}
	//else {
		//dir = LEFT;
	//}
	//
	//MOTOR_write(abs(gain),dir);
	
	//dt = TIMER_get_time(); //OBS må være en annen timer enn highscore
	//int16_t setpoint = (msg.data[2]);
	//int8_t encoder_val = PID_scale(MOTOR_read());
	/*int16_t encoder_val = PID_scale(MOTOR_read()); //value between 0 - 255
	printf("scala encoder val = %d\n", PID_scale(MOTOR_read()));
	int16_t current_error = ref - encoder_val;
	
	error_integrated = current_error*dt + error_integrated;
	
	if (current_error < 1){
		error_integrated = 0;
	}
	
	int16_t control_output = Kp*current_error + Ki*error_integrated;
	int16_t speed = 0;
	prev_error= current_error;
	int16_t current_pos = PID_scale(MOTOR_read());*/
	
	
	/*if (target_pos < current_pos)
	{
		printf("target < current\n");
		while (target_pos < / * PID_scale(MOTOR_read())* /current_pos) {
			//PORTH &= ~(1<<PH1);
			printf("current pos = %d\n target pos %d \n", current_pos, target_pos);
			//DAC_write(127);* /
			
			MOTOR_write_speed(127,RIGHT);
			_delay_ms(100);
		}
	}*/
	
	
	/*if (control_output < 0) {
		dir = LEFT;
		if (control_output > -150){
			speed = -control_output;
		}
		else{
			speed = 150;
		}
	}
	else{
		dir =RIGHT;
		if (control_output < 150){
			speed = control_output;
		}
		else{
			speed = 150;
		}
	}
	//MOTOR_write_speed(speed,dir);*/
	
	//printf("current_error = %d\n control output = %d\n error intgrated = %d\n",current_error,control_output,error_integrated);
	//MOTOR_write_pos(ref - control_output);
	//return control_output;
	//TIMER_start();
	
	}


void PID_init(void){
	//cli();
	//DAC_init();
	
	
	MOTOR_write_speed(127,LEFT);
	printf("GOIN RIGHT WROOM\n\n");
	_delay_ms(500);
	MOTOR_write_speed(0,LEFT);
	printf("rot_min before = %d\n", MOTOR_read());
	while (MOTOR_read()!= 0){
		_delay_ms(20);
		printf("IN THE SHIT");
		PORTH &= ~(1<<_RST);
		_delay_ms(20);
		PORTH |=  (1<<_RST);
		//void MOTOR_encoder_reset(void); //resetting the encoder so that rot_min = 0
	}
	rot_min = MOTOR_read();
	printf("rot_min = %d\n", MOTOR_read());
	_delay_ms(1000);
	
	
	MOTOR_write_speed(127,RIGHT);
	_delay_ms(500);
	MOTOR_write_speed(0,RIGHT);
	printf("rot_max = %d\n", MOTOR_read());
	rot_max = MOTOR_read();
	_delay_ms(1000);
	 
	
	MOTOR_write_speed(127,LEFT);
	_delay_ms(300);
	MOTOR_write_speed(0,LEFT);
	
	printf("PID_scale(rot_min) = %d\n", PID_scale(rot_min));
	printf("PID_scale(rot_max) = %d\n\n\n", PID_scale(rot_max));
	
	//step_size =( abs(rot_max) +abs(rot_min)) / 255;
	
	
	//cli();
	
	
	
	
	// start pid_timer with /1024 prescaler --> dt = 0.016
	TIMER_start(pid_timer);
	/*TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);*/
	printf("før sei");
	sei();
	
	
	/*MOTOR_write(127,LEFT);
	_delay_ms(70);
	MOTOR_write(0,LEFT);*/
	
/*
	printf("rot_min = %d\n", rot_min);
	printf("rot_max = %d\n", rot_max);
	
	printf("MOTOR_read() = %d\n", MOTOR_read());
	printf("(rot_max+rot_min)/2 = %d\n", (rot_max+rot_min)/2);*/

	/*while(MOTOR_read() < (rot_max+rot_min)/2) {
		printf("(rot_max+rot_min)/2 = %d\n", (rot_max+rot_min)/2);
		printf("MOTOR_read() = %d\n\n\n", MOTOR_read());
		MOTOR_write(127,LEFT);
	}*/
	
	
	//uint8_t motor_mid = abs((rot_max+rot_min)/2);
	
/*
	DAC_init();
	
	
	
	
	
	motor_mid = abs((rot_max+rot_min)/2);
	
	while(MOTOR_read() > motor_mid) {
		MOTOR_write(70,LEFT);
	}
	
	//MOTOR_write(0,right);*/
	
	/*cli();
	
	TIMSK2=(1<<TOIE2);
	
	
	// start pid_timer with /1024 prescaler --> dt = 0.016
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	
	sei();*/
	
}


uint16_t Slider_to_position_scale(int8_t encoder_val) {
	double val = (encoder_val)*(abs(rot_max)/255);
	return val;
}

void PID_update_ref(int16_t pos){
	ref_position = pos;
}

uint8_t PID_scale(int16_t encoder_val) {
	if (encoder_val < rot_max) {
		encoder_val = rot_max;
	}
	else if (encoder_val > rot_min) {
		encoder_val = rot_min;
	}
	
	uint8_t val = -(encoder_val *(255.0/rot_max));

		
	return 255-val;
}


int16_t PID_control(can_message_t msg) {
	 /*dt = TIMER_get_time(); //OBS må være en annen timer enn highscore*/
	int16_t setpoint = (msg.data[2]);
	//int8_t encoder_val = PID_scale(MOTOR_read());
	printf("setpoint = %d\n", setpoint);
	int16_t encoder_val = PID_scale(MOTOR_read()); //value between 0 - 255
	
	int16_t current_error = setpoint - encoder_val;
	
	error_integrated = current_error*dt + error_integrated;
	
	int16_t control_output = Kp*current_error + Ki*error_integrated;
	
	prev_error= current_error;
	
	/*if (control_output > 25) {
		control_output = 25;
	}
	else if (control_output < -25) {
		control_output = -25;
	} 
	else{
		control_output = 0;
	}*/
	printf("current_error = %d\n control output = %d\n error intgrated = %d\n",current_error,control_output,error_integrated);
	return control_output;
	
}

/*

uint8_t PID_get_rot_min(void) {
	return rot_min;
}

uint8_t PID_get_rot_max(void) {
	return rot_max;
}
*/


uint8_t PID_get_rot_max(void){
	return rot_max;
}


uint8_t PID_get_flag(void) {
	return pid_flag;
}