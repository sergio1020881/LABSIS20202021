/************************************************************************
Title: SUNTRACK.c
Author: Sergio Manuel Santos 
	<sergio.salazar.santos@gmail.com>
File: $Id: MAIN,v 1.8.2.1 21/10/2020 Exp $
Software: Atmel Studio 7 (ver 7.0.129)
Hardware: Atmega128 by ETT ET-BASE
	-PORTA LCD
	-PORTE Keyboard
	-PF0 Sensor LDR
	-PB6 Servo Motor
	-PORTD RTC
License: GNU General Public License
Comment:
	Excellence in progress
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
#define Min 500     // 450 PWM servo motor
#define Max 2350    // 2450 PWM servo motor
/*
** Global File variable
*/
struct time tm; // time struct RTC
struct date dt; // date struct RTC
/*
** Header
*/
void PORTINIT();
/****MAIN****/
int main(void)
{
	PORTINIT(); // Inic Ports
	/***INICIALIZE OBJECTS***/
	FUNC function= FUNCenable(); // Function Library
	LCD0 lcd0 = LCD0enable(&DDRA,&PINA,&PORTA); // LCD Display 4X20
	KEYPAD keypad = KEYPADenable(&DDRE,&PINE,&PORTE); // Keyboard
	ANALOG analog = ANALOGenable(1, 128, 1, 0); // Channel 0 for Position
	TIMER_COUNTER1 timer1 = TIMER_COUNTER1enable(9,0); // PWM Positioning
	PCF8563RTC rtc = PCF8563RTCenable(16); // RTC with I2C
	/******/
	char Menu='1'; // Main menu selector
	int16_t adcvalue; // analog reading
	char str[6]="0"; // analog vector
	int16_t mvalue=90; // manual position reading
	int16_t m_value; // manual positioning
	char mstr[6]="90"; // manual position vector
	char tstr[6]; // time vector
	char cal='0'; // Sub Menu for setting up date and time
	uint16_t set;
	/***Parameters timers***/
	timer1.compoutmodeB(2);
	timer1.compareA(20000);
	timer1.start(8);
	rtc.SetClkOut(1, 2); // oscillate pin at 1 sec
	/**********/
	//TODO:: Please write your application code
	while(TRUE){
		/***PREAMBLE***/
		lcd0.reboot();
		keypad.read();
		/***Reading input***/
		lcd0.gotoxy(3,13);
		lcd0.putch(':');
		lcd0.string_size(keypad.get().printstring,6);
		/***ENTRY END***/
		switch(Menu){
			/***MENU 1***/
			case '1': // Main Program Menu
				if(!strcmp(keypad.get().string,"A")){Menu='2';keypad.flush();lcd0.clear();break;}
				if(!strcmp(keypad.get().string,"B")){Menu='3';keypad.flush();lcd0.clear();break;}
					/***RTC***/
					tm=rtc.GetTime();
					dt=rtc.GetDate();
					/***Reading analog***/
					adcvalue=analog.read(0);
					/***Set Position***/
					timer1.compareB(function.trimmer(adcvalue,0,1023,Min,Max));
					lcd0.gotoxy(0,0);
					lcd0.string_size("Sense: ",7);
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
				break;
			/***MENU 2***/
			case '2': // Manual position override 
				if(!strcmp(keypad.get().string,"A")){Menu='3';keypad.flush();lcd0.clear();break;}
				if(!strcmp(keypad.get().string,"B")){Menu='1';keypad.flush();lcd0.clear();break;}
				if(!strcmp(keypad.get().string,"C")){Menu='1';keypad.flush();lcd0.clear();break;}
					lcd0.gotoxy(0,0);
					lcd0.string_size("Manual: ",8);
					lcd0.string_size(mstr,3);
					if(keypad.get().character==KEYPADENTERKEY){
						strncpy(mstr,keypad.get().string,6);
						mvalue=function.strToInt(mstr);
						if(mvalue >=0 && mvalue <181){
							m_value=mvalue;
							timer1.compareB(function.trimmer(m_value,0,180,Min,Max));
							lcd0.hspace(5);
						}else{
							lcd0.string_size("  err",5);
						}
						keypad.flush();
					}else
						timer1.compareB(function.trimmer(m_value,0,180,Min,Max));
					lcd0.gotoxy(3,0);
					lcd0.string_size("C - exit",8);
				break;
			/***MENU 3***/
			case '3': //Set Time and Date
				if(!strcmp(keypad.get().string,"A")){Menu='1';keypad.flush();lcd0.clear();break;}
				if(!strcmp(keypad.get().string,"B")){Menu='2';keypad.flush();lcd0.clear();break;}
				if(!strcmp(keypad.get().string,"C")){Menu='1';cal='0';keypad.flush();lcd0.clear();break;}
					/*** Menu to set RTC Time and Date ***/
					lcd0.gotoxy(0,0);
					lcd0.string_size("Date and Time Setup",19);
					/***Calibrate Menu***/
					switch(cal){
						case '0': // choice
							lcd0.gotoxy(1,0);
							lcd0.string_size("1-Year",7);
							lcd0.string_size("2-Month",8);
							lcd0.string_size("3-Day",5);
							lcd0.gotoxy(2,0);
							lcd0.string_size("4-Hour",7);
							lcd0.string_size("5-Min",8);
							lcd0.string_size("6-Sec",5);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							if(!strcmp(keypad.get().string,"1")){cal='1';keypad.flush();lcd0.clear();}
							if(!strcmp(keypad.get().string,"2")){cal='2';keypad.flush();lcd0.clear();}
							if(!strcmp(keypad.get().string,"3")){cal='3';keypad.flush();lcd0.clear();}
							if(!strcmp(keypad.get().string,"4")){cal='4';keypad.flush();lcd0.clear();}
							if(!strcmp(keypad.get().string,"5")){cal='5';keypad.flush();lcd0.clear();}
							if(!strcmp(keypad.get().string,"6")){cal='6';keypad.flush();lcd0.clear();}
							//if(keypad.get().character=='1'){cal='1';keypad.flush();lcd0.clear();}
							break;
						/********************************************************************/
						case '1': // YEAR
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Year:",11);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);	
							/***YEAR***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <100){
									rtc.SetYear(rtc.bintobcd(set));
									cal='0';
									}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
						break;
						/********************************************************************/
						case '2': // MONTH
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Month:",12);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							/***MONTH***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <13){
									rtc.SetMonth(rtc.bintobcd(set));
									cal='0';
								}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
							break;
						/********************************************************************/
						case '3': // DAY
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Day:",10);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							/***DAY***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <32){
									rtc.SetDay(rtc.bintobcd(set));
									cal='0';
								}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
						break;
						/********************************************************************/
						case '4': // HOUR
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Hour:",11);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							/***HOUR***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <24){
									rtc.SetHour(rtc.bintobcd(set));
									cal='0';
								}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
						break;
						/********************************************************************/
						case '5': // MINUTE
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Minutes:",13);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							/***MINUTE***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <60){
									rtc.SetMinute(rtc.bintobcd(set));
									cal='0';
								}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
						break;
						/********************************************************************/
						case '6': // SECOND
							lcd0.gotoxy(1,0);
							lcd0.string_size("Enter Seconds:",13);
							lcd0.gotoxy(3,0);
							lcd0.string_size("C - exit",8);
							/***SECOND***/
							if(keypad.get().character==KEYPADENTERKEY){
								strcpy(tstr,keypad.get().string);
								set=function.strToInt(tstr);
								if(set >=0 && set <60){
									rtc.SetSecond(rtc.bintobcd(set));
									cal='0';
								}else{
									strcpy(tstr,"err");
								}
								keypad.flush();
							}
						break;
						default:
							cal='0';
						break;
					};
				break;
				/********************************************************************/
			default:
				Menu='1';
				break;
		};
	}
}
/*
** procedure and function
*/
void PORTINIT(void)
{
	//INPUT
	DDRF=0x00;
	PORTF=0x0F;
	//OUTPUT
	DDRB|=(1<<5) | (1<<6) | (1<<7);
}
/*
** interrupt
*/
/***EOF***/
