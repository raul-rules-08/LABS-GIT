/*
 * File:   Libreria2.h
 * Author: Raul Aguilar
 *


 */
#pragma config FOSC = INTRC_NOCLKOUT //


char c;  //inicializamos variable c
char b;  //inicializamos variable b
float vpot1; //inicializamos la variable vpot1
float vpot2; //inicializamos la variable vpot2
char buffer []; //inicializamos la variable buffer

char revisa_char(void);                // USART

void display1 (void);        // Terminal virtual
void display2 (void);
void display3 (void);
void config (void); //inicializamos la funcion config
void Lcd_Set_Cursor(char x, char y); //inicializamos funcion que setea el cursor del lcd 
void Lcd_Write_String(char *a); //inicializamos funcion que escribe strings en la lcd 
void Lcd_Write_Char(char a); // inicializamos funcion que escribe chars en la lcd 
void Lcd_Port (char a);
void Lcd_Cmd (char a);
void Lcd_Init(void);                       

void Lcd_Shift_Left(void);
void Lcd_Shift_Right(void);
void contador_lcd (void);
void Lcd_Write_Char_4(char a);
void Conversion1(void);
void Conversion2(void);



void config (void){  
        
    ANSEL = 0b0000000;   //puerto a digital               
    ANSELH = 0b0000000;  //pueto a digital 
     
    TRISA = 0b00000011; //ponemos el puerto a en 0 con dos entradas analogicas               
    TRISB = 0b00000000; //ponemos el puerto b en 0             
    TRISD = 0b00000000; //ponemos el puerto d en 0    
    
    ANSELbits.ANS0 = 1;     //entrada anlogica    AN0
    ANSELbits.ANS1 = 1;     //entrada anlogica    AN1
          
    
    ADCON0bits.ADON=1;     //encendemos el adc           
    ADCON1bits.ADFM=0;     //justificacion de bits            
    
    INTCONbits.GIE = 1;     //interrupciones globales    
    INTCONbits.PEIE = 1;    //interrupciones perifericas 

    PIE1bits.ADIE = 1;        //interrupciones del ADC de conversion
    PIR1bits.ADIF = 0;        //interrupciones del adc 

 
}

void Lcd_Cmd(char a){       //se cargan los comandos a la lcd para inicializacion asi como para limpiar la lcd 
	PORTDbits.RD2 =0;       //ponemos en 0 para poder escribir valores a la lcd 
	PORTB=a;          // cargamos lo que se desea escribir a la lcd 
    PORTDbits.RD3=1;     //seteamos en uno la lcd para que lea los valores cargados              
    __delay_ms(4);      
    PORTDbits.RD3=0;    //regresamos a 0 esperando leer algo mas               
}


Lcd_Clear(){ //se limpia la lcd utilizando los comandos de la misma 
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) //funcion para setear el cursor de la lcd 
{
	char temp,z,y; //variables char 
	if(a == 1)
	{
	  temp = 0x80 + b - 1; //calculo de la posicion del cursor 
		//z = temp>>8;
		//y = temp & 0x0F;
		Lcd_Cmd(temp); //mandamos los valores al lcd para leer la posicion del cursor 
		
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1; //calculo de la posicion del cursor 
		//z = temp>>8;
		//y = temp & 0x0F;
		Lcd_Cmd(temp); //mandamos los valores al lcd para leer la posicion del cursor 
		
	}
}

void Lcd_Write_Char(char a){    
    PORTDbits.RD2 = 1; //mantenemos en 1 la lcd para que pueda leer el char que le mandemos           
    PORTB = a;         //mandamos el valor a la lcd        
    PORTDbits.RD3=1;   //leemos el valor del char                    
    __delay_us(40);              
    PORTDbits.RD3=0;    //esperamos que otro valor ingrese a la lcd                  
}

void Lcd_Write_String(char *a)
{
	int i;// inicialiamos la variable i
	for(i=0;a[i]!='\0';i++) //for que usamos para leer el strings dependiendo del tamano 
	    Lcd_Write_Char(a[i]); //mandamos el char a la lcd 
}

void Lcd_Init(){           
    
    PORTDbits.RD2 = 0;   //podemos el lcd en 0 para poder leer los comandos                
       
    Lcd_Cmd(0x00);      // utilizamos el conamdo 0x00       
    __delay_ms(15);         
    
   
    Lcd_Cmd(0x30);       // utilizamos el conamdo 0x30        
    __delay_us(160);        
    
    Lcd_Cmd(0x38);     // utilizamos el conamdo 0x38  
    Lcd_Cmd(0x0D);     // utilizamos el conamdo 0x0D         
    Lcd_Cmd(0x01);     // utilizamos el conamdo 0x01         
    Lcd_Cmd(0x06);     // utilizamos el conamdo 0x06        
   
}
