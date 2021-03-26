/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define RGBLEDG GREEN_LED
#define RGBLEDR RED_LED
#define RGBLEDB BLUE_LED
#define LEDA0  PA_7
#define LEDA1  PA_6
#define LEDA2  PA_5
#define LEDA3  PB_4
#define LEDA4  PE_5
#define LEDA5  PE_4
#define LEDA6  PB_1
#define LEDA7  PB_0

#define LEDB0  PB_5
#define LEDB1  PE_3
#define LEDB2  PE_2
#define LEDB3  PE_1
#define LEDB4  PD_3
#define LEDB5  PD_2
#define LEDB6  PD_1
#define LEDB7  PD_0

void Winner1F(void);
void semaforo(void);
void player1 (void);
void mostrar_led(void);
void Winner2F(void);
void player2(void);
void mostrar_led2(void);
const int pushButton1= PUSH1;
const int pushButton2= PUSH2;
int Start=0;
int leerpush1 = 0;
int leerpush2 = 0;
int contador = 0;
int contador2 = 0;
int libera = 0;
int libera2 = 0;
int access = 0;
int winner1=0;
int winner2=0;
int i = 0;
int i2 = 0;
int presionado1;
int presionado2;
//see pins_energia.h for more LED definitions
//#define LED GREEN_LED
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  //PLAYER1 LEDS
  pinMode(LEDA0, OUTPUT);
  pinMode(LEDA1, OUTPUT);
  pinMode(LEDA2, OUTPUT);
  pinMode(LEDA3, OUTPUT);
  pinMode(LEDA4, OUTPUT);
  pinMode(LEDA5, OUTPUT);
  pinMode(LEDA6, OUTPUT);
  pinMode(LEDA7, OUTPUT);
  
  //PLAYER2 LEDS
  pinMode(LEDB0, OUTPUT);
  pinMode(LEDB1, OUTPUT);
  pinMode(LEDB2, OUTPUT);
  pinMode(LEDB3, OUTPUT);
  pinMode(LEDB4, OUTPUT);
  pinMode(LEDB5, OUTPUT);
  pinMode(LEDB6, OUTPUT);
  pinMode(LEDB7, OUTPUT);

  
  pinMode(RGBLEDG, OUTPUT); 
  pinMode(RGBLEDR, OUTPUT); 
  pinMode(RGBLEDB, OUTPUT); 
  pinMode(pushButton1, INPUT_PULLUP);   
  pinMode(pushButton2, INPUT_PULLUP);     
}

// the loop routine runs over and over again forever:
void loop() {
    leerpush1=digitalRead(pushButton1);
    leerpush2=digitalRead(pushButton2);

if (winner1 ==0 && winner2==0 && access==0){  // Si winner 1 , winner 2 y access son igual a 0 ejecuta el codigo
  if ((leerpush1)==0||(leerpush2)==0)         // Si se presiona el push 1 o el push 2 dos se ejecuta semaforo
       {
       semaforo();                            // Se va a funcion semaforo
       } 
       
}
if (winner1 ==0 && winner2==0 && access==1){ // Si winner 1 , winner 2  son igual a 0 pero access es igual a uno ejecuta el codigo
  player1();                                 // LLama a las funciones Player 1
  mostrar_led();                             //Llama a la funcion mostrar_Led
  player2();                                  // LLama a las funciones Player 2
  mostrar_led2();                              //Llama a la funcion mostrar_Led2
} 
else {                                         // En otro caso si Winner es igual a 1 ejecuta la funcion Winner1 F
     if (winner1 ==1)
      {
       Winner1F();
      }
     if (winner2==1)                           // En otro caso si Winner2 es igual a 1 ejecuta la funcion Winner2 F
     {
       Winner2F(); 
     }
    }
}
void semaforo (void) {                        // La funcion semaforo muestra una secuencia de color para que se preparen los jugadores
  
  digitalWrite(RGBLEDG, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(RGBLEDR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDB, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                  // wait for a second
  digitalWrite(RGBLEDG, HIGH);   // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDR, HIGH);   // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDB, LOW);   // turn the LED off by making the voltage LOW
  delay(3000);                 // wait for a second
  digitalWrite(RGBLEDG, LOW);  // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDR, HIGH);  // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDB, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);               // wait for a second
  digitalWrite(RGBLEDG, LOW);  // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDR, LOW);  // turn the LED off by making the voltage LOW
  digitalWrite(RGBLEDB, LOW);    // turn the LED off by making the voltage LOW
  access = 1;
 
}

void player1(void)                      //Funcion del contador del jugador 1 con su antirebote
{
   if (leerpush1 == 0)                 //Revisa si se presiona el boton
    {
    contador = contador + 1;          //Contaador de reconocimineto
    libera   = 0;                     
    if ( contador > 500)              //Revisa si el contador no se a sobre pasado
    {
      if (presionado1 == 0)           //Revisa si el botno se a presionado
      {
           i= i+1;                    //Se le suma a la variable uno
           presionado1 = 1;           //Se afirma que se presiono
      }
      contador = 0;                   //Se reinicia el contador de reconocieminto
    }
   }
  else
  {
    libera = libera+1;                // contado de reconocimineto suelto
    contador = 0;                     //Contador en 0
    if (libera > 500)                //revisa si se a sobre pasado
    { 
      presionado1 = 0;                //se dejo de presionar
      libera = 0 ;                   //Se reinica liberado
    }
  }
}
void player2(void) 
{
   if (leerpush2 == 0)         //Revisa si se presiona el boton
    {
    contador2 = contador2 + 1;
    libera2   = 0;
    if ( contador2 > 500)
    {
      if (presionado2 == 0)
      {
           i2= i2+1;
           presionado2 = 1;
      }
      contador2 = 0;
    }
   }
  else
  {
    libera2 = libera2+1;
    contador2 = 0;
    if (libera2 > 500)
    { 
      presionado2 = 0;
      libera2 = 0 ;
    }
  }
}
void mostrar_led(void){
  switch(i){

   case 1:
   digitalWrite(LEDA0, HIGH);
   break;

   case 2:
   digitalWrite(LEDA1, HIGH);
   break;

   case 3:
   digitalWrite(LEDA2, HIGH);
   break;

   case 4:
   digitalWrite(LEDA3, HIGH);
   break;

   case 5:
   digitalWrite(LEDA4, HIGH);
   break;

   case 6:
   digitalWrite(LEDA5, HIGH);
   break;

   case 7:
   digitalWrite(LEDA6, HIGH);
   break;

   case 8:
   digitalWrite(LEDA7, HIGH);
   winner1 = 1;
   break;
  }
}
void mostrar_led2(void){
  switch(i2){

   case 1:
   digitalWrite(LEDB0, HIGH);
   break;

   case 2:
   digitalWrite(LEDB1, HIGH);
   break;

   case 3:
   digitalWrite(LEDB2, HIGH);
   break;

   case 4:
   digitalWrite(LEDB3, HIGH);
   break;

   case 5:
   digitalWrite(LEDB4, HIGH);
   break;

   case 6:
   digitalWrite(LEDB5, HIGH);
   break;

   case 7:
   digitalWrite(LEDB6, HIGH);
   break;

   case 8:
   digitalWrite(LEDB7, HIGH);
   winner2 = 1;
   break;
  }
}
 void Winner1F(void){
 digitalWrite(RGBLEDG, HIGH);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(RGBLEDR, HIGH);    
 digitalWrite(RGBLEDB, HIGH);
 delay(1000);               // wait for a second
 digitalWrite(RGBLEDG, LOW);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(RGBLEDR, LOW);    
 digitalWrite(RGBLEDB, LOW);
 delay(1000);        
 }
 void Winner2F(void){
 digitalWrite(RGBLEDG, HIGH);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(RGBLEDR, HIGH);    
 digitalWrite(RGBLEDB, HIGH);
 delay(1000);               // wait for a second
 digitalWrite(RGBLEDG, LOW);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(RGBLEDR, LOW);    
 digitalWrite(RGBLEDB, LOW);
 delay(1000);        
 }
