#pragma config FOSC =INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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


#include "SPI.h"
#include "LCD.h"
#include <xc.h>
#include "PIC16F887.h" //libreria del pic 
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>

void setup(void);
void Contador(void);
void conversion(void);
void temperaturac(void); // funcion temperatura

void main(void) {
    
    setup();
    Lcd_Init();                         //inicializar la lcd 
    Lcd_Set_Cursor(1,1);                //cursor para escribir 
    Lcd_Write_String("DIGITAL 2");      //escribimos las letras en pantalla
    Lcd_Set_Cursor(2,1);                //cursor para escribir 
    Lcd_Write_String("RAUL AGUILAR");   //escribimos las letras en pantalla
    __delay_ms(100); 
    Lcd_Clear();                        // limpiamos lo escrito de la lcd 
    
     Lcd_Set_Cursor(1,1);               //cursor para escribir       
     Lcd_Write_String("Cont");          //escribimos las letras en pantalla
     Lcd_Set_Cursor(1,8);
     Lcd_Write_String("ADC"); 
      Lcd_Set_Cursor(1,14);
     Lcd_Write_String("Temp"); 
                                        //cursor para escribir       
     
     
    while(1){
        PORTCbits.RC2 = 0;  //selesccionamos esclavo_1
       __delay_ms(5);
       spiWrite(PORTB);    //escrimos el valor del puerto b de regreso
       contm = spiRead();  //leemos el valor que mandamos del esclavo y lo metemos en contm
       Contador();         //llamamos la funcion contador 
       __delay_ms(5);
       PORTCbits.RC2 = 1;  //apagamos el esclavo
     ////////////////////////////////////////////////////////////////////////////////////////////////////
       
       PORTCbits.RC1 = 0;  //seleccionamos el esclavo_2
        __delay_ms(5);
        spiWrite(PORTB);   //escribimos el valor del puerto de regreso
        c = spiRead();     //leemos el valor que mandamos del esclavo y lo metemos en c 
        conversion();      //llamamos la funcion conversion
        __delay_ms(5);
      PORTCbits.RC1 = 1;   //apagamos el esclavo 
     //////////////////////////////////////////////////////////////////////////////////////////////////////   
      
      PORTCbits.RC0 = 0;   //seleccionamos el Slave_3
        __delay_ms(5);
        spiWrite(PORTB);   //mandamos el valor del peurto b de regreso
        cc = spiRead();    //leemos el valor del esclavo y lo metemos en cc 
        temperaturac();    //llamamos la funcion temperatura c 
        __delay_ms(5);
      PORTCbits.RC0 = 1;   //apagamos el esclavo 
        
    }       
        
    return;
}

void setup(void){  //funcion setup para los pines 
    ANSEL = 0;
    ANSELH = 0;
    
    TRISC2 = 0;
    TRISC1 = 0;
    TRISC0 = 0;
    
    TRISB = 0;
    TRISD = 0;
    TRISA = 0;
    
    PORTB = 0;
    PORTD = 0;
    PORTA = 0;
    
    PORTCbits.RC2 = 0; //ponemos el modo esclavo del pic
    PORTCbits.RC1 = 0; //ponemos el modo esclavo del pic 
    PORTCbits.RC0 = 0; //ponemos el modo esclavo del pic 
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    //inicializamos el esclavo
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
    while ( !SSPSTATbits.BF );
}

void spiWrite(char dat)  
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

void Contador(void){ 
      
      sprintf(buffer1,"%.3f",contm);  // convertimos el valor del pot a letras para que pueda ser impreso en la pantalla
      Lcd_Set_Cursor(2,1);        
      Lcd_Write_String(buffer1);
}

void conversion(void){
       
        vpot1 = (5*c)/255;                //valor del voltaje del potenciometo
        sprintf(buffer2, "%.2f", vpot1);  // convertimos el valor del pot a le tras para que pueda ser impreso en la pantalla
        Lcd_Set_Cursor(2,8);        
        Lcd_Write_String(buffer2); 
}
void temperaturac(void){
        tempt = (cc*5.0/255)*100;         //valor de la temperatura
        sprintf(buffer3, "%.1f", tempt);  // convertimos el valor del sensor a letras para que pueda ser impreso en la pantalla
        Lcd_Set_Cursor(2,13);        
        Lcd_Write_String(buffer3); 
}