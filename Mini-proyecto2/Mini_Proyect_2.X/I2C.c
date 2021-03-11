#include <xc.h>
#include "I2C.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void I2C_Init(const unsigned long a){
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*a))-1;
    SSPSTAT = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void I2C_M_Wait(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

//*****************************************************************************	//*****************************************************************************
// Master inicializar comunicacion
//*****************************************************************************	//*****************************************************************************

void I2C_M_Start()	{
    I2C_M_Wait();      //esperar
    SSPCON2bits.SEN = 1;    //inicia la comunicación i2c
}

//*****************************************************************************	//*****************************************************************************
// Restablecer comunicacion	
//*****************************************************************************	//*****************************************************************************

void I2C_M_Restart(){
	I2C_M_Wait();      //esperar
    SSPCON2bits.RSEN = 1;   //reinicia la comunicación i2c
}

//*****************************************************************************	//*****************************************************************************
//Detener comunicacion
//*****************************************************************************	//*****************************************************************************

void I2C_M_Stop(){
    I2C_M_Wait();      //esperar
    SSPCON2bits.PEN = 1;    //detener la comunicación i2c
}

//*****************************************************************************	//*****************************************************************************
//Escribir a esclavo (devuelve 0)
//*****************************************************************************	//*****************************************************************************

void I2C_M_Write(unsigned a){
    I2C_M_Wait();      //esperar
    SSPBUF = a;             
}

//*****************************************************************************	//*****************************************************************************
//Leer datos de esclsvo
//*****************************************************************************	//*****************************************************************************

unsigned short I2C_M_Read(unsigned short a){
    unsigned short temp;
    I2C_M_Wait();      
    RCEN = 1;
    I2C_M_Wait();      
    temp = SSPBUF;
    I2C_M_Wait();      
    if(a == 1){
        SSPCON2bits.ACKDT = 0;
    }
    else{
        SSPCON2bits.ACKDT = 1;
    }
        SSPCON2bits.ACKEN = 1;          // Acknowledge
    return temp;                    // Regresar dato leído
}

//*****************************************************************************	//*****************************************************************************
// inicializar I2C Esclavo	
//*****************************************************************************	//*****************************************************************************

void I2C_S_Init(uint8_t address){ 
    SSPADD = address;
    SSPCON = 0x36;      // 0b00110110
    SSPSTAT = 0x80;     // 0b10000000
    SSPCON2 = 0x01;     // 0b00000001
    TRISC3 = 1;
    TRISC4 = 1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}