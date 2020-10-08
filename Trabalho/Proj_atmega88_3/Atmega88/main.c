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
#define Datapin 4
#define Clkpin 5
#define Outpin 7
/***Global Variable***/
/***Procedure & Function Def***/
void PORTINIT();
void shift_bit(uint8_t bool, uint8_t datapin, uint8_t clkpin);
void shift_byte(uint8_t byte, uint8_t datapin, uint8_t clkpin, uint8_t outpin);
void shift_data(uint8_t byte, uint8_t datapin, uint8_t clkpin, uint8_t outpin);
/***MAINMAIN***/
int main(void)
{
	//uint8_t i;
	PORTINIT();
    /* Replace with your application code */
	PORTD &= ~(1<<Outpin); //Output clock
	PORTD &= ~(1<<Clkpin); //Shift CLOCK input disable
    while (TRUE)
    {
		
		//for(i=0;i<8;i++)
			//shift_bit(1);
		 
		//for(i=0;i<8;i++)
			//shift_bit(0);
			
		shift_data(85, 4, 5, 7);
		shift_data(170, 4, 5, 7);
		shift_data(255, 4, 5, 7);
		shift_data(0, 4, 5, 7);
			
    }
}
void PORTINIT()
{
	DDRD = (1<<Datapin); //Serial Data
	DDRD |= (1<<Clkpin); //Serial Clock
	DDRD |= (1<<Outpin); //Serial Store
	PORTD = ~(1<<Datapin); //Serial Data
	PORTD &= ~(1<<Clkpin); //Serial Clock
	PORTD &= ~(1<<Outpin); //Serial Store
}
void shift_bit(uint8_t bool, uint8_t datapin, uint8_t clkpin)
{
	_delay_ms(100);
	if (bool)
		PORTD |= (1<<datapin); //Data bit HIGH
	else
		PORTD &= ~(1<<datapin); //Data bit LOW
	PORTD |= (1<<clkpin); // Shift bit
	PORTD &= ~(1<<clkpin); //Shift disable
}
void shift_byte(uint8_t byte, uint8_t datapin, uint8_t clkpin, uint8_t outpin)
{
	uint8_t i;
	for(i=0;i<8;i++)
		shift_bit(byte & (1<<i), datapin, clkpin);
	PORTD |= (1<<outpin); //Output enable
	PORTD &= ~(1<<outpin); //Output disable
}
void shift_data(uint8_t byte, uint8_t datapin, uint8_t clkpin, uint8_t outpin)
{
	uint8_t i;
	for(i=0;i<8;i++)
		shift_bit(byte & (1<<i), datapin, clkpin);
	PORTD |= (1<<outpin); //Output enable
	PORTD &= ~(1<<outpin); //Output disable
}
/***EOF***/
