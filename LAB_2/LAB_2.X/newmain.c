/*
 * File:   Laboratorio 2
 * Author: Raul A
 *
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#include "ADC.h"



void __interrupt() ISR(void){
       
    if (TMR0IF == 1 ){   // interrupcion del TIMER 0 que manda a colocar el valor del contador en el puerto A 
        desplegar();
        //TOGGLE();       // y a multiplexar los displays 
        TMR0IF=0;
        TMR0= 2;
        PORTA = i;
        return;
    }
    if (INTCONbits.RBIF ==1 ){
        INTCONbits.RBIF = 0;          // interrupcion del puerto B para sumar y restar en el contador binario.
        di(); 
        
        operacion();
       
        return;
    }
    if (PIR1bits.ADIF ==1){
        
        PIR1bits.ADIF = 0;              // interrupcion del ADC que guarda en un registro el valor de la conversion analogica a digital.
        
        //z = ADRESH;
        //x = ADRESL;
        //y = ADRESL;
       
        
        return;
    }
        
}
    

void main(void)
{
    setup();                // el main  en donde llama la funcion setup para configurar puertos/entradas y modulos.
    analogico();            // manda llamar a otra funcion para el desarrollo del codigo en el circuito
    return;
}
    
    void analogico(void){
        while(1){
            
            
            if (ADRESL >i){          // en un loop infinito estara constantemente revisando los valores del contador y del ADC para la alarma
                ALARMA = 1;
            }
            if (ADRESL <=i){
                ALARMA = 0;
            }
            ADCON0bits.GO_DONE = 1;
        __delay_ms(10);
        if(ADCON0bits.GO_DONE == 0){            // cuando go done se apague se prende de nuevo para iniciar nueva conversion ADC
            //NIBBLES();
            x = ADRESL;
            y = ADRESL;
             //desplegar();                       // manda a llamar la funcion desplegar de los 7 segmentos
               
        }
        
       
       
        }
        
    }