
/*
 * File:   USART1.h
 * Author: Raul Aguilar
 *

 */
#ifndef USART_H
#define	USART_H
#include <xc.h>               
#include <stdint.h>          
#include <stdio.h>     
#include "USARTx.h"
#define _XTAL_FREQ 9000000
         


void  USART_lib_config(void){
    
    SPBRG = 57;  
     
    TXSTAbits.CSRC = 0;     // No importa, solo para sincrono
    TXSTAbits.TX9  = 0;     // 8 bits
    TXSTAbits.TXEN = 1;     // Permitir transmision
    TXSTAbits.SYNC = 0;     // Asincrono
    TXSTAbits.BRGH = 1;     // Alta velocidad por 4Mhz   
    RCSTAbits.SPEN = 1;     // Permitir puerto serial
    RCSTAbits.RX9  = 0;     // 8 bits
    RCSTAbits.SREN = 0;     // No importa solo para asincrono
    RCSTAbits.CREN = 1;     // Permitir recibir 
    PIR1bits.RCIF = 0;      // Bandera recibir apagada   
    PIR1bits.TXIF = 0;      // Bandera transmitir apagada
    
}   
#endif	/* USART_H */