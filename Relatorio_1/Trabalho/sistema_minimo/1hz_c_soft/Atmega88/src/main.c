/***PreProcessor***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
/***Library***/
#include <avr/io.h >
#include <avr/interrupt.h >
#include <util/delay.h >
#include <avr/pgmspace.h >
/***Define and Macro***/
#define TRUE 1
/***Global Variable***/
/***Prototype***/
void PORTINIT(void);
/***MAIN***/
int main(void)
{
	uint8_t i,j,k;
	PORTINIT();
	while(TRUE)
	{
		for(i=32; i; i--){
			for(j=166; j; j--){
				for(k=250; k; k--);
			}
		}
		PORTD^= (1<<PORTD6);
	}
}
/***Procedure and Function***/
void PORTINIT(void){
	DDRD=(1<<PORTD6);
	PORTD=(1<<PORTD6);
}
/***Interrupt***/
/***EOF***/
