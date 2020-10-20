/************************************************************************
Title:    SUNTRACK.c
Author:   Sergio Manuel Santos <sergio.salazar.santos@gmail.com>
File:     $Id: MAIN,v 1.8.2.1 2015/04/11 13:00:00 sergio Exp $
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: 
    Atmega128 by ETT ET-BASE
	-PORTA LCD
	-PORTC Keyboard
	-PF0 Sensor LDR
	-PB6 Servo Motor
	
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
#include <stdlib.h>
#include <string.h>
/**********/
#include "atmega128analog.h"
#include "atmega128timer.h"
#include "function.h"
#include "lcd.h"
#include "clock.h"
#include "mm74c923.h"
#include "keypad.h"
/*********/
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
	KEYPAD keypad = KEYPADenable(&DDRE,&PINE,&PORTE);
	ANALOG analog = ANALOGenable(1, 128, 1, 0); // channel 0 for position
	TIMER_COUNTER0 timer0 = TIMER_COUNTER0enable(2,2); // for clock
	TIMER_COUNTER1 timer1 = TIMER_COUNTER1enable(9,0); // PWM positioning
	//TIMER_COUNTER3 timer3 = TIMER_COUNTER3enable(12,12);
	relogio=CLOCKenable(12,0,0);
	/******/
	char Menu='1';
	int adcvalue;
	char str[4]="0";
	int mvalue=90;
	char mstr[4]="90";
	/***Parameters timers***/
	timer0.compare(249);
	timer1.compoutmodeB(2);
	timer1.compareA(20000);
	timer1.start(8);
	timer0.start(64);
	//timer3.compoutmodeC(1);
	//timer3.start(255);
	/**********/
	//TODO:: Please write your application code
	while(TRUE){
		//PREAMBLE
		lcd0.reboot();
		keypad.read();
		/***Entry Start***/
		lcd0.gotoxy(3,0);
		lcd0.putch(keypad.get().character);
		lcd0.gotoxy(3,10);
		lcd0.string_size(keypad.get().printstring,10);
		/***ENTRY END***/
		switch(Menu){
			case '1': //Show readings
				if(!strcmp(keypad.get().string,"A")){
					Menu='2';
					//cleanup
					strcpy(mstr,"");
					lcd0.clear();
					keypad.flush();
				}else{
					/***Reading analog***/
					adcvalue=analog.read(0);
					/***Set Position***/
					timer1.compareB(function.trimmer(adcvalue,0,1023,450,2450));
					lcd0.gotoxy(0,0);
					lcd0.string_size("Sensor:",7);
					//lcd0.hspace(1);
					strcpy(str,function.i16toa(adcvalue));
					lcd0.string_size(str,4);
				}
				break;
			case '2':
				if(!strcmp(keypad.get().string,"A")){
					Menu='3';
					//cleanup
					lcd0.clear();
					keypad.flush();
				}else{
					lcd0.gotoxy(0,0);
					lcd0.string_size("Manual:",7);
					lcd0.string_size(mstr,4);
					if(keypad.get().character==KEYPADENTERKEY){
						strcpy(mstr,keypad.get().string);
						mvalue=function.strToInt(mstr);
						if(mvalue >=0 && mvalue <=180){
							timer1.compareB(function.trimmer(mvalue,0,180,450,2450));
						}else{
							strcpy(mstr,"err");
						}
						keypad.flush();
					}
				}
				break;
			case '3':
				if(!strcmp(keypad.get().string,"A")){
					Menu='1';
					//cleanup
					lcd0.clear();
					keypad.flush();
				}else{
					lcd0.gotoxy(1,0);
					lcd0.string_size("Nothing to see here!",20);
				}
				break;
			default:
				lcd0.gotoxy(0,0);
				lcd0.string_size(keypad.get().string,5);
				if(!strcmp(keypad.get().string,""));
				else
					strcpy(str,keypad.get().string);
				timer1.compareB(function.trimmer(function.strToInt(str),0,1023,450,2450));
				break;
		};
		lcd0.gotoxy(0,12);
		lcd0.string(relogio.show());
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
