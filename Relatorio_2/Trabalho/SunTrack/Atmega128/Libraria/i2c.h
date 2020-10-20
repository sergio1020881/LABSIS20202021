/***************************************************************************************************
I2C API START
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
Date: 20102020
Comment:
	Stable
 **************************************************************************************************/
#ifndef _I2C_H
	#define _I2C_H
/***Function Prototypes***/
void I2C_Init(uint8_t prescaler);
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t );
uint8_t I2C_Read(uint8_t);
uint8_t I2C_status(void);
/******/
#endif
/***EOF***/
