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
/***MAINMAIN***/
int main(void)
{
	uint8_t count=0;
	PORTINIT();
    /* Replace with your application code */
	PORTD = ~(1<<7); //output clock
	PORTB = ~(1<<ZERO); //shift CLOCK input disable
    while (TRUE)
    {	
		while(!count){
		/***1***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***2***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***3***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***4***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***5***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***6***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***7***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/***8***/
		_delay_ms(1000);
		PORTD = (1<<4); //Data Serial in high
		PORTB = (1<<ZERO); // shift CLOCK input read
		//PORTD = (1<<7); //output clock
		PORTB = ~(1<<ZERO); //shift CLOCK input disable
		//PORTD = ~(1<<7); //output clock
		/******/
		PORTD = (1<<7); //output clock
		PORTD = ~(1<<7); //output clock
		/******/
		count++;
		}
		
    }
}
void PORTINIT()
{
	DDRB = (1<<ZERO); //Serial Clock
	DDRD = (1<<4); //Serial Data
	DDRD = (1<<7); //Serial Store
	PORTB = ~(1<<ZERO);
	PORTD = ~(1<<4);
	PORTD = ~(1<<7);
}
