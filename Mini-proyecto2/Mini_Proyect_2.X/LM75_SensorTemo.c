#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
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
#pragma config WRT = OFF      

#include <xc.h>
#include "PIC16F887.h"
#include <stdlib.h>
#include "I2C.h"
#include "I2C_USART.h"  
#include "OSC.h"  
#include <stdint.h>
#define CDC_DATA_OUT_EP_SIZE 64
#define CDC_DATA_IN_EP_SIZE 64
#define _XTAL_FREQ 80000000
#define SDA TRISBbits.TRISB4 // I2C bus
#define SCL TRISBbits.TRISB6


unsigned char Byte1;
unsigned char Byte2;
unsigned int Int1; 
int sensor ;
char Estado;
char COMPARE = 0;

//function
void setup(void);
void USART_config(void); 
void escribir_char (uint8_t valor);
void interrup_config (void);
char leer_char(void);
void USART_SendString();



//unsigned char readBuffer[CDC_DATA_IN_EP_SIZE];
void main(void){
    setup();
    I2C_Init(100000);
    USART_config(); 
    //USART_Init(9600);
    char buffer[20]; 
    int Temp;
    

      while(1)
      {
      I2C_M_Start();
      sensor = I2C_M_Read (0);
      I2C_M_Stop();I2C_M_Read;
      
    
      __delay_ms(200);
     
      //Temp = sensor/4;
  
//Take values in buffer to send all parameters over USART 

      sprintf(buffer, "%d \r\n",sensor);
      USART_SendString(buffer);
      }
}
  
 
void setup(void) 
{ 
    
    ANSEL = 0;                // Puerto A dig 
    TRISA = 0;                // Puerto a OUT
    PORTA = 0;                // Puerto A entrada apagado
    ANSELH = 0;               // Puerto B dig
    TRISB = 0;                // Puerto B out
    PORTB = 0;                // Puerto B apagado
    TRISC = 0;                // Puerto C OUT
    PORTC = 0;                // Puerto C apagado
    TRISCbits.TRISC6 = 0;     // TX salida
    
    TRISD = 0;                // Puerto D salida 
    PORTD = 0;                // Puerto D apagados
    TRISE = 0;                // Puerto E salida
    PORTE = 0;                // Puerto E apagado
    TRISEbits.TRISE0 = 0;     // TX salida
    TRISEbits.TRISE3 = 0;     // TX salida
    InitOSC(7);
    
}

void USART_config(void) 
{     

    USART_lib_config();       // USART
}

void escribir_char (uint8_t valor)
{

    TXREG = valor;                     // Se envia Byte a TXREG
    while (PIR1bits.TXIF == 0);        // Espera a que se haya enviado dato
}


void USART_SendString(const char *str)
{

   while(*str!='\0')
   {                /* Transmit data until null */
              
        escribir_char(*str);
        str++;
   }
}

char leer_char(void)
{
    if (RCSTAbits.OERR ==0)
    {            // Hay error?
    
        CREN = 0;                      // Apagar modulo para apagar error
        NOP();
        CREN = 1;                      // Enciende una vez no haya error
    }
    return (RCREG);                    // Se envia valor a RCREG
 
}




