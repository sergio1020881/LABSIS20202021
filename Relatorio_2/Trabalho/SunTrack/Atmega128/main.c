/************************************************************************
Title:		SUNTRACK.c
Author:  Sergio Manuel Santos 
	<sergio.salazar.santos@gmail.com>
File:  $Id: MAIN,v 1.8.2.1 20/10/2020 Exp $
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: 
    Atmega128 by ETT ET-BASE
	-PORTA LCD
	-PORTE Keyboard
	-PF0 Sensor LDR
	-PB6 Servo Motor
	-PORTD RTC
License:  GNU General Public License
Comment:
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
#include "atmega128analog.h"
#include "atmega128timer.h"
#include "function.h"
#include "lcd.h"
#include "pcf8563rtc.h"
#include "keypad.h"
/*
** Constant and Macro
*/
#define TRUE 1
#define ZERO 0
/*
** Global File variable
*/
struct time tm;
struct date dt;
/*
** Header
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
	TIMER_COUNTER1 timer1 = TIMER_COUNTER1enable(9,0); // PWM positioning
	//TIMER_COUNTER3 timer3 = TIMER_COUNTER3enable(12,12);
	PCF8563RTC rtc = PCF8563RTCenable(16);
	/******/
	char Menu='1';
	int adcvalue;
	char str[4]="0";
	int mvalue=90;
	char mstr[4]="90";
	char cal='0';
	/***Parameters timers***/
	timer1.compoutmodeB(2);
	timer1.compareA(20000);
	timer1.start(8);
	rtc.SetClkOut(1, 2);
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
			case '1': //Main Program Menu
				if(!strcmp(keypad.get().string,"A")){
					Menu='2';
					//cleanup
					strcpy(mstr,"");
					lcd0.clear();
					keypad.flush();
				}else if(!strcmp(keypad.get().string,"B")){
					Menu='3';
					//cleanup
					strcpy(mstr,"");
					lcd0.clear();
					keypad.flush();
				}else{
					/***RTC***/
					tm=rtc.GetTime();
					dt=rtc.GetDate();
					/***Reading analog***/
					adcvalue=analog.read(0);
					/***Set Position***/
					timer1.compareB(function.trimmer(adcvalue,0,1023,450,2450));
					lcd0.gotoxy(0,0);
					lcd0.string_size("Sensor:",7);
					//lcd0.hspace(1);
					strcpy(str,function.i16toa(adcvalue));
					lcd0.string_size(str,4);
					lcd0.gotoxy(0,12);
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(dt.days)),2);
					lcd0.putch(':');
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(dt.century_months)),2);
					lcd0.putch(':');
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(dt.years)),2);
					lcd0.gotoxy(1,12);
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(tm.hours)),2);
					lcd0.putch(':');
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(tm.minutes)),2);
					lcd0.putch(':');
					lcd0.string_size(function.ui16toa(rtc.bcd2dec(tm.VL_seconds)),2);
				}
				break;
			case '2': // Manual position override 
				if(!strcmp(keypad.get().string,"A")){
					Menu='3';
					//cleanup
					lcd0.clear();
					keypad.flush();
				}else if(!strcmp(keypad.get().string,"B")){
					Menu='1';
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
			case '3': //Set Time and Date
				if(!strcmp(keypad.get().string,"A")){
					Menu='1';
					//cleanup
					lcd0.clear();
					keypad.flush();
				}else if(!strcmp(keypad.get().string,"B")){
					Menu='2';
					//cleanup
					lcd0.clear();
					keypad.flush();
				}else{
					/*** Menu to set RTC Time and Date ***/
					switch(cal){
						case '0':
							lcd0.gotoxy(0,0);
							lcd0.string_size("Date and Time Setup",19);
							lcd0.gotoxy(1,0);
							lcd0.string_size("1-Year",6);
							cal=keypad.get().character;
						case '1':
							lcd0.string_size("  Not Yet",9);
							keypad.flush();
						break;
						default:
						break;
					};
				}
				break;
			default:
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
}
/*
** interrupt
*/
/***EOF***/
