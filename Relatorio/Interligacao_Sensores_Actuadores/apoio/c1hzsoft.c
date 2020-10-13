/*
 * _1Hz_Em_C_Por_Software.c
 *
 */ 
/***PreProcessor***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
/***Library***/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
/***Define and Macro***/
#define TRUE 1
/***Global Variable***/
/***Prototypes***/
void PORTINIT(void);
/***MAIN***/
int main(void)
{
	uint8_t i,j,k;
	PORTINIT();
    while(TRUE)
    {
        //TODO:: Please write your application code
		for(i=32;i;i--){//delay 32
			for(j=166;j;j--){//nested loop 166
				for(k=250;k;k--);
			}
		}
		PORTD^=(1<<PORTD6);
	}
}
//32*166*250
/***Procedure and Function***/
void PORTINIT(void){
	DDRD=(1<<PORTD6);
	PORTD=(1<<PORTD6);
}
/***Interrupt***/
/***EOF***/
