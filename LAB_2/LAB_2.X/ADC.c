#include <xc.h>
#include "ADC.h"




void setup(void){
  // oscilador interno
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 0;
    
    
     //entradas, salidas, entradas digitales o analogicas
    ANSEL = 0b00000000;
    ANSELH = 0b00100000;
    TRISA = 0b00000000;
    TRISB = 0b00100011; 
    
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    // adc configuration bits
                 
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 1;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 1;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON0bits.GO_DONE = 0;
    
    //timer 0 configuration bits
    OPTION_REGbits.nRBPU = 1;
    OPTION_REGbits.INTEDG = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b010; // 1:2 tmr0 rate 
    TMR0 = 2;
   
    // interrupciones intcon
    INTCONbits.GIE = 1;
   
    INTCONbits.T0IE= 1;
    
    
    INTCONbits.T0IF= 0;
    
    
    
    
    
    // interrupciones ADC
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
  
    INTCONbits.PEIE = 1;
    
    // interrupciones on change PORTB
    INTCONbits.RBIF= 0;
    INTCONbits.RBIE= 1;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    // valores iniciales de variables
    i = 0;
    z = 0;
    ALARMA = 0;
    seg1 = 0;
    seg2 = 0;
    y=0;
    x=0;
    BANDERA = 0;
}
 void TOGGLE (void){       // valor de la bandera ira alternando para multiplexar 7 segmentos
        if(BANDERA==1){
            BANDERA =0;
            return;
        }
        else{
            BANDERA = 1;
            return;
        }
    } 
 
  void NIBBLES(void){           // funcion que separa los valores de cada nibble para su respectivo 7 segmentos  byte 00000000 nibble 0000 bit 0 
        x = ADRESL/16 ; 
        y = ADRESL%16 ; 
        
        return;
        
    }
  void desplegar(void){    // dependiendo del valor de la bandera elige el transistor prender y asi colocar el numero a desear, multiplexacion
       NIBBLES();
       char mostrar = 0;
       //PORTC = 0;
        seg1 = 0;
        seg2 = 0;
        if(BANDERA ==1){
            mostrar = x;
            PORTC = DISPLAY1[mostrar];
            seg1 = 1;
            seg2 = 0;
           
           // return;
        }
        if(BANDERA == 0){
            mostrar = y;
            PORTC = DISPLAY2[mostrar];
            seg2 = 1;
            seg1 = 0;
               
            //return;
        }
         TOGGLE();
         

    }
  
  void operacion (void){        // incrementa o decrementa el valor del contador binario.
      if (RESTA == 1){
           ANTIREBOTEA = 1;
           di();         
       }
        if(RESTA == 0 && ANTIREBOTEA ==1 ){
            ANTIREBOTEA = 0;
            
            ADC++; //adc=adc+1;
            
            i = ADC;
            ei();
            return;
 
        }
        
       if(SUMA == 1 ){
            ANTIREBOTEB= 1;
            di();
            
        }
       if(SUMA == 0 && ANTIREBOTEB ==1){
            ANTIREBOTEB= 0;
            ADC--;
            
            i = ADC;
            ei();
            return;
              
    }
  }