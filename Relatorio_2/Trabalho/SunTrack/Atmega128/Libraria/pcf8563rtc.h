/***************************************************************************************************
PCF8563RTC API START
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
Date: 20102020
Comment:
	Stable
 **************************************************************************************************/
#ifndef _PCF8563RTC_H_
	#define _PCF8563RTC_H_
/******/
#include <inttypes.h>
/******/
#define PCF8563ReadMode_U8   0xA3  // PCF8563 ID
#define PCF8563WriteMode_U8  0xA2  // PCF8563 ID
#define PCF8563SecondRegAddress_U8   0x02   // Address to access PC8563 SEC register
#define PCF8563DateRegAddress_U8     0x05   // Address to access PC8563 DATE register
#define PCF8563ControlRegAddress_U8  0x00   // Address to access PC8563 CONTROL register
#define PCF8563CLKOUT_control_U8     0x0D	// External oscillating pin
/******/
struct date{
	uint8_t years;
	uint8_t century_months;
	uint8_t weekdays;
	uint8_t days;	
};
struct time{
	uint8_t hours;
	uint8_t minutes;
	uint8_t VL_seconds;
};
struct alarm{
	uint8_t minute_alarm;
	uint8_t	hour_alarm;
	uint8_t day_alarm;
	uint8_t weekday_alarm;
	
};
/***Function Prototypes***/
struct pcfrtc{
	void (*SetTime)(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8);
	void (*SetClkOut)(uint8_t onoff, uint8_t freq);
	void (*SetDate)(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8);
	struct time (*GetTime)(void);
	struct date (*GetDate)(void);
	uint8_t (*bcd2dec)(uint8_t num);
	uint8_t (*bintobcd)(uint8_t bin);
};
typedef struct pcfrtc PCF8563RTC;
PCF8563RTC PCF8563RTCenable(uint8_t prescaler);
/******/
#endif
/***EOF***/
