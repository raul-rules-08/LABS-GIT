//============================================================================*/
// LIBRERIA
//============================================================================*/

#ifndef I2C_USART_H
#define	I2C_USART_H
#include <pic16f887.h>           // Include PIC18F4550 header file 
#define _XTAL_FREQ 8000000       // Frecuencia compilador
#include <xc.h>                  // XC8 libreria     
#include <stdint.h>              // Variables de ancho definido   
#include <stdio.h>               // Tipos de variables, macros, entradas y salidas

//============================================================================*/
// PROTOTIPO DE FUNCIONES
//============================================================================*/
void USART_Init(long);
void USART_lib_config(void);  
void USART_TxChar(char);            /* USART character transmit function */
char USART_RxChar();                /* USART character receive function */
void USART_SendString(const char *);/* USART String transmit function */
void MSdelay(unsigned int val);     /* millisecond delay function */


#endif	/* I2C_USART_H */