/***PreProcessor***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
/***Library***/
#include <avr/interrupt.h >
#include <util/delay.h >
#include <avr/io.h >
#include <avr/pgmspace.h >
/***Define and macro***/
#define TRUE 1
#define REPEAT 100
/***Global variable***/
int count;
/***Prototype***/
void PORTINIT(void);
void TIMER0ASETUP(void);
/***MAIN***/
int main(void)
{
	PORTINIT();
	TIMER0ASETUP();
	count = REPEAT;
	while(TRUE)
	{
	}
}
/***Procedure and function***/
void PORTINIT(void){
	DDRD = (1<<PORTD6);
	PORTD = (1<<PORTD6);
}
void TIMER0ASETUP(void){
	uint8_t sreg;
	sreg = SREG;
	cli();
	/***Periodo de 10ms***/
	TCCR0A = (1<<WGM01);
	TIMSK0 = (1<<OCIE0A);
	OCR0A = 156;
	TCCR0B |= (1<<CS02);
	SREG = sreg;
	sei();
}
/***Interrupt***/
ISR(TIMER0_COMPA_vect){
	count--;
	if(!count){
		PORTD^= (1<<PORTD6);
		count = REPEAT;
	}
}
/***EOF***/
