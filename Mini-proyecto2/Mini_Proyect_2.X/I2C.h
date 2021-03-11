#ifndef __I2C_MASTER_H
#define	__I2C_MASTER_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <pic16f887.h>

void I2C_Init(const unsigned long c);

void I2C_M_Wait();

void I2C_M_Start();

void I2C_M_Restart();

void I2C_M_Stop();

void I2C_M_Write(unsigned d);

unsigned short I2C_M_Read(unsigned short a);

void I2C_S_Init(uint8_t address);

#endif	/* XC_HEADER_TEMPLATE_H */
