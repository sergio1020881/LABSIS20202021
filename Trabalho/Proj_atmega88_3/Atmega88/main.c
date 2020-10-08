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
/***MAINMAIN***/
int main(void)
{
	uint8_t i;
	PORTINIT();
    /* Replace with your application code */
	PORTD &= ~(1<<7); //output clock
	PORTD &= ~(1<<5); //shift CLOCK input disable
    while (TRUE)
    {
		
		for(i=0;i<8;i++)
			shift_bit(1);
		 
		for(i=0;i<8;i++)
			shift_bit(0);
			
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
		PORTD |= (1<<4); //Data Serial in high
	else
		PORTD &= ~(1<<4); //Data Serial in high
	PORTD |= (1<<5); // shift CLOCK input read
	PORTD |= (1<<7); //output clock
	PORTD &= ~(1<<5); //shift CLOCK input disable
	PORTD &= ~(1<<7); //output clock
}
