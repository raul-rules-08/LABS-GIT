/*
 * File:   newmain.c
 * Author: Fernando Figueroa
 *
 * Created on January 23, 2021, 12:38 PM
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
#include "SPI3.h"//libreria qcreada 
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>

void conversion (char puertoANL);
void config(void);


 void __interrupt() ISR(void) {
    
     if (PIR1bits.ADIF ==1){ // configuracion de la interrupcion
        PIR1bits.ADIF = 0;   
        cc = ADRESH; //valor de la conversion     
    }
      if(SSPIF == 1){
        //PORTD = spiRead(); //esto le escribe al puerto del esclavo
        spiWrite(cc);
        SSPIF = 0;
    }
 }
   
void main(void) {
    config(); //configuracion de los puertos 
    Lcd_Init(); //inicializar la lcd 
    Lcd_Set_Cursor(1,1); //cursor para escribir 
    Lcd_Write_String("DIGITAL 2");//escribimos las letras en pantalla
    Lcd_Set_Cursor(2,1); //cursor para escribir 
    Lcd_Write_String("Raul Aguilar"); //escribimos las letras en pantalla
    __delay_ms(100); 
    Lcd_Clear();// limpiamos lo escrito de la lcd 
    
     Lcd_Set_Cursor(1,1);  //cursor para escribir       
     Lcd_Write_String("Temp"); //escribimos las letras en pantalla
     
    
    while(1){
                     
        conversion(0);  //se manda a llamar la funcion conversion con 0 como valor para indentificar que puerto analogico esta trabajndp       
        
    }
}


void conversion(char puertoANL){  //funcion conversion la cual hace la conversion del valor del adc a voltaje y identifica para cual puerto es cada valor con un if
    
    ADCON0bits.CHS = puertoANL;   
    if (ADCON0bits.GO_DONE==0 && puertoANL ==0){ // bit de conversion e 0 indicando que no ha empezado y puerto analogico en 0 para determinar cual puerto es el que se utiliza 
        
        temp = (cc*5.0/255)*100; 
        if (temp < 24){
            PORTEbits.RE0 = 1;
            PORTEbits.RE1 = 0;
            PORTEbits.RE2 = 0;
        }
        if(temp > 25 && temp < 35){
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 1;
            PORTEbits.RE2 = 0;
        }
        if(temp > 36){
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 0;
            PORTEbits.RE2 = 1;
        }
        sprintf(bufferr, "%.3f", temp);  // convertimos el valor del pot a le tras para que pueda ser impreso en la pantalla
        Lcd_Set_Cursor(2,1);        
        Lcd_Write_String(bufferr); //escribimos el valor de buffer el cual contiene el valor del potenciometro 
        ADCON0bits.GO_DONE=1; //empezamos la conversion del adc 
    }
    
}    

void config(void){
    ANSEL =  0b0000000;   //puerto a digital               
    ANSELH = 0b0000000;  //pueto a digital 
     
    TRISA = 0b00000001; //ponemos el puerto a en 0 con dos entradas analogicas               
    TRISB = 0b00000000; //ponemos el puerto b en 0             
    TRISD = 0b00000000; //ponemos el puerto d en 0    
    TRISE = 0b000;
    
    PORTE = 0;
    
    ANSELbits.ANS0 = 1;     //entrada anlogica    AN0
    ANSELbits.ANS1 = 1;     //entrada anlogica    AN1
          
    //
    ADCON0bits.ADON=1;     //encendemos el adc           
    ADCON1bits.ADFM=0;     //justificacion de bits            
    
    INTCONbits.GIE = 1;      //interrupciones globales    
    INTCONbits.PEIE = 1;     //interrupciones perifericas 

    PIE1bits.ADIE = 1;          //interrupciones del ADC de conversion
    PIR1bits.ADIF = 0;          //interrupciones del adc 
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}

void spiWrite(char dat)  //Write data to SPI bus
{
    SSPBUF = dat;
}

unsigned spiDataReady() //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char spiRead() //REad the received data
{
    spiReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}