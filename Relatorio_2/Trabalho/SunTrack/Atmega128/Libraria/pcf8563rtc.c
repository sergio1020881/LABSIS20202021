/***************************************************************************************************
PCF8563RTC API START
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
Date: 20102020
Comment:
	Stable
 **************************************************************************************************/
/***Library***/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "pcf8563rtc.h"
#include "i2c.h"
/***Define***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
/***Global File Variables***/
/***void PCF8563RTC_Init(uint8_t prescaler)***/
void PCF8563RTC_Init(uint8_t prescaler)
{
	I2C_Init(prescaler);					// Initialize the I2c module.
	I2C_Start();							// Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);			// Connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563ControlRegAddress_U8);	// Select the PCF8563 ControlRegister to configure PCF8563
	I2C_Write(0x00);						// Write 0x00 to Control register to disable SQW-Out
	I2C_Stop();								// Stop I2C communication after initializing PCF8563
}
/***void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)***/
void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
{
	I2C_Start();                            // Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);         // connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563SecondRegAddress_U8);  // Select the SEC RAM address
	I2C_Write(var_sec_u8);			        // Write sec from RAM address 00H
	I2C_Write(var_min_u8);			        // Write min from RAM address 01H
	I2C_Write(var_hour_u8);			        // Write hour from RAM address 02H
	I2C_Stop();           	                // Stop I2C communication after Setting the Time
}
/***void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq)***/
void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq)
{
	uint8_t word=0;
	if(onoff)
		word=0x80 | (freq & 0x03);
	I2C_Start();                            // Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);			// connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563CLKOUT_control_U8);	// Select the CLKOUT RAM address
	I2C_Write(word);						// Write Clock from RAM address 0DH						
	I2C_Stop();           	                // Stop I2C communication after Setting the Time
}
/***void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8)***/
void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8)
{
	I2C_Start();                          // Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);	      // connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563DateRegAddress_U8);  // Request DAY RAM address at 04H
	I2C_Write(var_day_u8);			      // Write date on RAM address 04H
	I2C_Write(var_weekday_u8);
	I2C_Write(var_month_u8);			  // Write month on RAM address 05H
	I2C_Write(var_year_u8);			      // Write year on RAM address 06h
	I2C_Stop();				              // Stop I2C communication after Setting the Date
}
/***struct time PCF8563RTC_GetTime(void)***/
struct time PCF8563RTC_GetTime(void)
{
	struct time result;
	I2C_Start();							       // Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);			       // connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563SecondRegAddress_U8);	       // Request Sec RAM address at 00H
	I2C_Stop();								       // Stop I2C communication after selecting Sec Register
	I2C_Start();							       // Start I2C communication
	I2C_Write(PCF8563ReadMode_U8);			       // connect to PCF8563(Read mode) by sending its ID
	result.VL_seconds = I2C_Read(1) & ~0x80;	   // read second and return Positive ACK
	result.minutes = I2C_Read(1) & ~0x80;		   // read minute and return Positive ACK
	result.hours = I2C_Read(0) & ~0xC0;			   // read hour and return Negative/No ACK
	I2C_Stop();								       // Stop I2C communication after reading the Time
	return result;
}
/***struct date PCF8563RTC_GetDate(void)***/
struct date PCF8563RTC_GetDate(void)
{
	struct date result;
	I2C_Start();							        // Start I2C communication
	I2C_Write(PCF8563WriteMode_U8);			        // connect to PCF8563 by sending its ID on I2c Bus
	I2C_Write(PCF8563DateRegAddress_U8);	        // Request DAY RAM address at 04H
	I2C_Stop();								        // Stop I2C communication after selecting DAY Register
	I2C_Start();							        // Start I2C communication
	I2C_Write(PCF8563ReadMode_U8);			        // connect to PCF8563 (Read mode) by sending its ID
	result.days = I2C_Read(1) & ~0xC0;				// read Day and return Positive ACK
	result.weekdays = I2C_Read(1) & ~0xF8;			// read Month and return Positive ACK
	result.century_months = I2C_Read(1) & ~0xE0;
	result.years = I2C_Read(0);				        // read Year and return Negative/No ACK
	I2C_Stop();								        // Stop I2C communication after reading the Date
	return result;
}
/***uint8_t PCF8563RTC_bcd2dec(uint8_t num)***/
uint8_t PCF8563RTC_bcd2dec(uint8_t num)
{
	return ((num/16 * 10) + (num % 16));
}
/***uint8_t  PCF8563RTC_bintobcd(uint8_t bin)***/
uint8_t  PCF8563RTC_bintobcd(uint8_t bin)
{
	return (((bin) / 10) << 4) + ((bin) % 10);
}
/***EOF***/
