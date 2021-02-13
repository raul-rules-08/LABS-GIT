/*
 * File:   lab3.c
 * Author: Raul Aguilar
 *

 */

//configuracion del programa 
// CONFIG1
#pragma config FOSC =INTRC_NOCLKOUT// Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#define _XTAL_FREQ  9000000 //frecuencia
#include <xc.h>
#include "PIC16F887.h" //libreria del pic 
#include "Libreria2.h"//libreria qcreada 
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>
#include "USART.h"             

//VARIABLES
   uint8_t enteroc ;
   uint8_t decima1c  ;
   uint8_t centena1c ; 
   uint8_t decima2c  ;
   uint8_t centena2c ;
   uint8_t enterob ;
   uint8_t decima1b ;
   uint8_t centena1b; 
   uint8_t decima2b ;
   uint8_t centena2b ;
   uint8_t velocidad1 = 0;         
   uint8_t velocidad2 = 0;   
   uint8_t velocidad3 = 0; 
   uint8_t contador;
   uint8_t revisa;
   uint8_t valor=0;
   uint8_t w1;                     
   uint8_t w2;
   uint8_t a;
  
void conversion (char puertoANL);
void dato_char (uint8_t valor);
void USART_config(void);
            



 void __interrupt() ISR(void) {
    
     if (PIR1bits.ADIF ==1){ // configuracion de la interrupcion
        PIR1bits.ADIF = 0; 
      
        c = ADRESH;           //valor de la conversion 
        b = ADRESH;           //valor de la conversion
    } 
     
    if (PIR1bits.RCIF == 1)       //Interupción de recepcion de datos                                           
    {
        revisa = revisa_char();   //revisa y guarda el dato
        PIR1bits.RCIF = 0;        // Se apaga si no ha un dato
    }
 }
   
void main(void) {
    config();                      //configuracion de los puertos 
    Lcd_Init();                    //inicializar la lcd 
    Lcd_Set_Cursor(1,1);            //cursor para escribir 
    Lcd_Write_String("DIGITAL 2");   //escribimos las letras en pantalla
    Lcd_Set_Cursor(2,1);             //cursor para escribir 
    Lcd_Write_String("RAUL_AGUILAR"); //escribimos las letras en pantalla
    __delay_ms(100); 
    Lcd_Clear();                     // limpiamos lo escrito de la lcd 
    
     Lcd_Set_Cursor(1,1);         //cursor para escribir       
     Lcd_Write_String("Volt1");   //escribimos las letras en pantalla
     Lcd_Set_Cursor(1,7);          //cursor para escribir       
     Lcd_Write_String("Volt2");    //escribimos las letras en pantalla
     Lcd_Set_Cursor(1,13);         //cursor para escribir       
     Lcd_Write_String("Contador"); //escribimos las letras en pantalla
     USART_config();
     
    while(1){
              
        conversion(1);  //se manda a llamar la funcion conversion con 1 como valor para indentificar que puerto analogico       
        conversion(0);  //se manda a llamar la funcion conversion con 0 como valor para indentificar que puerto analogico  
        
    }
}
void  dato_char (uint8_t valor)
{
    TXREG = valor;                    // Se envia Byte a TXREG
    while (PIR1bits.TXIF == 0);      // Espera a que se haya enviado dato
}

char revisa_char(void){             // Funcion de revicion de datos 

    if (RCSTAbits.OERR ==0)         // Evalua si hay error
    {
        CREN = 0;                   // Apaga  
        NOP();                      // delay
        CREN = 1;                   // Enciende   
    }
    return (RCREG);                    
}

void  USART_config() {              // Se llama a la configurcion de USART
    
  USART_lib_config();
}



void conversion(char puertoANL){  //funcion conversion la cual hace la conversion del valor del adc a voltaje 
    
    ADCON0bits.CHS = puertoANL;   
    if (ADCON0bits.GO_DONE==0 && puertoANL ==0){ // bit de conversion e 0 indicando que no ha empezado y puerto analogico en 0 para determinar cual puerto es el que se utiliza 
        
        vpot1 = (5*c)/255; //valor del voltaje del potenciometo
       
        Lcd_Set_Cursor(2,1);        
        Conversion1 ();  
        ADCON0bits.GO_DONE=1; //empezamos la conversion del adc 
    }
    else{
        vpot2 = (5*b)/255;  //valor del voltaje del potenciometo       
        
        Lcd_Set_Cursor(2,7); 
        Conversion2(); 
        ADCON0bits.GO_DONE=1; //empezamos la conversion del adc }
        
        contador_lcd();     
     
    if (contador < 10)                    // se revisa si es menor
    {
        Lcd_Set_Cursor(2,14);            // se setea el cursor
        Lcd_Write_Char(contador + 48);    // Se escribe
    }
    else if (contador >= 10)                 // Mayor a 10?
    {
        w1 = contador/10;                    // Decena
        w2 = contador % 10;                  // Unidad
        Lcd_Set_Cursor(2,13);                // Cursor en columna 13
        Lcd_Write_Char(w1+48);               // Se escriben valores
        Lcd_Write_Char(w2+48);
    }
    }
}    

void Conversion1(){                          //funcion Conversion1 toma la variable c y lo divide en carecteres de 8 bits
    
    enteroc = (c*2)/100;                     
    decima1c = enteroc%100;                  
    centena1c = decima1c /10; 
    decima2c = decima1c % 10;
    centena2c = decima2c/1;
    Lcd_Write_Char(enteroc+48);
    Lcd_Write_Char(46);
    Lcd_Write_Char(centena1c+48);
    Lcd_Write_Char(centena2c+48);
    Lcd_Write_Char(86);
    display1();    
}

void Conversion2(){                          // La funcion Conversion2 toma la variable b y lo divide en carecteres de 8 bits
    
    
    enterob = (b*2)/ 100;                     
    decima1b = enterob%100;
    centena1b = decima1b /10; 
    decima2b = decima1b % 10;
    centena2b = decima2b/1;
    Lcd_Write_Char(enterob+48);
    Lcd_Write_Char(46);
    Lcd_Write_Char(centena1b+48);
    Lcd_Write_Char(centena2b+48);
    Lcd_Write_Char(86);
    display2 ();  
    display3();
    
}
void display1 (void)                // La funcion toma y lo manda al TXREG
{
    
    {
         dato_char (83);      // caracter s
         dato_char(49);          // caracter 1
         dato_char(58);         // caracter :
         dato_char(enteroc+48);  // Unidad  ASCII                                               
         dato_char(46);          // caracter .
         dato_char(centena1c+48); // Primer digito
         dato_char(centena2c+48); // Segundo digito
         dato_char(86);          // caracter V
         dato_char(32);         // espaciado
         dato_char(32);          // espaciado   
     
    }
}   
void display2 (void)                   // La funcion toma y lo manda al TXREG   
{
       
    {
         dato_char(83);        // caracter s
         dato_char(50);       //caracter 1
         dato_char(58);     //caracter :
         dato_char(enterob+48);  // Unidad en ASCII                                                    
         dato_char(46);      // caracter.
         dato_char(centena1b+48);// Primer digital
         dato_char(centena2b+48);// Segundo digital
         dato_char(86);      // caracter V
         dato_char(32);         // espaciado
         dato_char(32);          // espacisdo
        
    }
}

void display3 (void)
{
   
    {
        if (contador  < 10)             
        {
             dato_char(67);         // Caracteres de la tabla s
             dato_char(58);        // Caracteres de la tabla :
             dato_char(48);       // Caracteres de la tabla 0
             dato_char(contador+48); // Contador + ASCII     
             dato_char('\r');        // Caracteres de la tabla enter
                           
        }
        else
        {
             dato_char(67);         // Caracteres de la tabla C
             dato_char(58);        // Caracteres de la tabla :
             dato_char(w1+48);    // Decena ASCII
             dato_char(w2+48);       // Unidad ASCII 
             dato_char('\r');         // Caracteres de la tabla enter
            
        }
    }
}
void contador_lcd (void)           // Funcion que revisa si existe + o - en la funcion        
{
    if (revisa == '+')         // Revisa si hay un mas
    {
        contador = contador + 1;   // Contador + 1
        revisa = 0;               // Ya no se revisa
    }  
    
    
    else if (revisa == '-')     // Revisa si hay un -
       {
        contador = contador - 1;   // Contador - 1
        revisa = 0;                  // Se deja de revisar
        }
}


