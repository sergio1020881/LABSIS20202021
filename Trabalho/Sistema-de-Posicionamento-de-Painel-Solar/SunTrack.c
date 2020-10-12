/************************************************************************
Title:    SUNTRACK.c
Author:   Sergio Manuel Santos <sergio.salazar.santos@gmail.com>
File:     $Id: MAIN,v 1.8.2.1 2015/04/11 13:00:00 sergio Exp $
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: 
    Atmega128 by ETT ET-BASE
License:  GNU General Public License
Usage:    see Doxygen manual
LICENSE:
    Copyright (C) 2014
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
COMMENT:
	In Progress
************************************************************************/
#define F_CPU 16000000UL
/*
** library
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
/**********/
#include "function.h"
#include "lcd.h"
#include "analog.h"
#include "timer.h"
#include "clock.h"
#include "mm74c923.h"
/*********/
#include<string.h>
/*
** constant and macro
*/
#define TRUE 1
#define FALSE 0
#define GI 7
#define vector_size 16
/*
** variable
*/
uint16_t TIMER0_COMPARE_MATCH;
CLOCK relogio;
/*
** procedure and function header
*/
void PORTINIT();
/****MAIN****/
int main(void)
{
	PORTINIT();
	/***INICIALIZE OBJECTS***/
	FUNC function= FUNCenable();
	LCD0 lcd0 = LCD0enable(&DDRA,&PINA,&PORTA);
	MM74C923 keypad = MM74C923enable(&DDRC,&PINC,&PORTC);
	ANALOG analog = ANALOGenable(1, 128, 1, 0); // channel 0 for position
	TIMER_COUNTER0 timer0 = TIMER_COUNTER0enable(2,2); // for clock
	TIMER_COUNTER1 timer1 = TIMER_COUNTER1enable(9,0); // PWM positioning
	relogio=CLOCKenable(12,0,0);
	/******/
	char Mode='1';
	char keytmp[8];
	char analogtmp[8];
	char keychar;
	int adcvalue;
	uint8_t step=0;
	/***Parameters timers***/
	timer0.compare(249);
	timer1.compoutmodeB(2);
	timer1.compareA(20000);
	timer1.start(8);
	timer0.start(64);
	/**********/
	while(TRUE){
		//PREAMBLE
		lcd0.reboot();
		keypad.activate();
		//TODO:: Please write your application code
		switch(Mode){
			case '1':
				lcd0.gotoxy(0,0);
				lcd0.string_size(keypad.gets(),5);
				if(!strcmp(keypad.data(),""));
				else
					strcpy(keytmp,keypad.data());
				timer1.compareB(function.trimmer(function.strToInt(keytmp),0,180,450,2450));
				break;
			case '2':
				lcd0.gotoxy(0,0);
				adcvalue=analog.read(0);
				function.itoa(adcvalue,analogtmp);
				lcd0.string_size(analogtmp,5);
				timer1.compareB(function.trimmer(adcvalue,0,1023,450,2450));
				break;
			default:
				lcd0.gotoxy(0,0);
				lcd0.string_size(keypad.gets(),5);
				if(!strcmp(keypad.data(),""));
				else
					strcpy(keytmp,keypad.data());
				timer1.compareB(function.trimmer(function.strToInt(keytmp),0,1023,450,2450));
				break;
		};
		lcd0.hspace(3);
		lcd0.string(relogio.show());
		/***Menu***/
		keychar=keypad.getch();
		switch(step){
			case 0:
				lcd0.gotoxy(0,1);
				lcd0.string_size("Menu -> R+1",12);	
				lcd0.hspace(4);
				switch(keychar){
					case 'Q':
						step=1;
					break;
				};
				break;
			case 1:
				lcd0.gotoxy(0,1);
				lcd0.string_size("M-1 | A-2 | T-3",15);
				lcd0.hspace(1);
				switch(keychar){
					case '1':
						Mode='1';
						step=0;
						keypad.data_clear();
						break;
					case '2':
						Mode='2';
						step=0;
						keypad.data_clear();
						break;
					case '3':
						step=2;
						break;
				};
				break;
			case 2:
				step=0;
				keypad.data_clear();
				break;
		};
	}
}
/*
** procedure and function
*/
void PORTINIT()
{
	//INPUT
	DDRF=0x00;
	PORTF=0x0F;
	DDRE=0X00;
	PORTE=0XFF;
	DDRD=0X00;
	PORTD=0XFF;
	//OUTPUT
	DDRC=0XFF;
	PORTC=0x00;
	DDRB|=(1<<5) | (1<<6) | (1<<7);
	//UART0
	//DDRE=0X02;
	SREG|=(1<<GI);
}
/*
** interrupt
*/
ISR(TIMER0_COMP_vect) // TIMER0_COMP_vect used for clock
{
	TIMER0_COMPARE_MATCH++;
	if(TIMER0_COMPARE_MATCH > 999){
		TIMER0_COMPARE_MATCH=0;
		relogio.increment();
	}
}
/***EOF***/
/***COMMENTS
set hour mode
***/
