/******************************************
	Atmega88.c
Created: 08/10/2020 13:13:01
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
*******************************************/
/***preamble inic***/
#define F_CPU 8000000UL
/*
** library
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
/***Constant and Macros***/
#define TRUE 1
#define ZERO 0
/***Global Variable***/
/***Procedure & Function Def***/
void PORTINIT();
void shift_bit(uint8_t bool);
void shift_byte(uint8_t byte);
/***MAINMAIN***/
int main(void)
{
	//uint8_t i;
	PORTINIT();
    /* Replace with your application code */
	PORTD &= ~(1<<7); //output clock
	PORTD &= ~(1<<5); //shift CLOCK input disable
    while (TRUE)
    {
		
		//for(i=0;i<8;i++)
			//shift_bit(1);
		 
		//for(i=0;i<8;i++)
			//shift_bit(0);
			
		shift_byte(85);
		shift_byte(170);
		shift_byte(255);
		shift_byte(0);
			
    }
}
void PORTINIT()
{
	DDRD = (1<<4); //Serial Data
	DDRD |= (1<<5); //Serial Clock
	DDRD |= (1<<7); //Serial Store
	PORTD = ~(1<<4); //Serial Data
	PORTD &= ~(1<<5); //Serial Clock
	PORTD &= ~(1<<7); //Serial Store
}
void shift_bit(uint8_t bool)
{
	_delay_ms(100);
	if (bool)
		PORTD |= (1<<4); //Data bit HIGH
	else
		PORTD &= ~(1<<4); //Data bit LOW
	PORTD |= (1<<5); // shift bit
	PORTD &= ~(1<<5); //shift disable
}
void shift_byte(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
		shift_bit(byte & (1<<i));
	PORTD |= (1<<7); //output enable
	PORTD &= ~(1<<7); //output disable
}