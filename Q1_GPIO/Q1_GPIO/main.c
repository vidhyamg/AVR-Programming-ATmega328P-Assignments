/*
 * Q1_GPIO.c
 *program to toggle an LED connected to PORTD Pin 5 with specific timing intervals for the ON and OFF states.
 */ 
#define F_CPU 16000000UL  //clock speed=16MHZ
#include <avr/io.h>       //input/output
#include<util/delay.h>    //delay


int main(void)
{
	//PORTD PIN-HIGH-OUTPUT
	
	//DDRD = 0b00100000;  //making PORT D as output
	DDRD|=(1 << DDD5);
	while (1)
	{
		//PORTD PIN2 HIGH
		
		//PORTD = 0b00000100;  //turn on
		PORTD |= (1<< PD5);
		_delay_ms(3000);      //3 sec delay
		
		//PORTD PIN2 LOW
		//PORTD = 0b00000000;  //turn off
		PORTD &= ~(1<< PD5);
		_delay_ms(5000);      //5 sec delay
	}
}

