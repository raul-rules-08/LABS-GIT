/*
  LABORATORIO 5
  RAUL ESTUARDO AGUILAR RECINOS
  17581
  DIGITAL 2
 */
#include <SPI.h>
#include <SD.h>
int option;
File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  SPI.setModule(0);


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}

void loop(){
  if (Serial.available()>0){                        // Obtiene el numero de bytes disponibles para la lectura del puerto serial.
    option=Serial.read();                           //Lee el byte enviado y lo guarda en la variable.
    
     if(option=='2'){                               //Si la opción es igual a 2.
      
       root = SD.open("Falcon.txt");
        if (root) { 
         while (root.available())                   // Lee del archivo hasta que ya no haya nada en el.
           {Serial.write(root.read());}
         root.close();}  // close the file:
              
        else {
        Serial.println("error opening test.txt");    // Si el archivo no se abre se imprime un error.
            }
        }
          
     if(option=='3'){
      
      root = SD.open("Pokeball.txt");                //Si la opción es igual a 3 
      
       if (root) {
        while (root.available())                     // Lee del archivo hasta que ya no haya nada en el.
           {Serial.write(root.read());}
        root.close();}  // close the file:
          
        else {
        Serial.println("error opening test.txt");    // Si el archivo no se abre se imprime un error.
            }
        }
        
     if(option=='4'){
        
      root = SD.open("Skull.txt");
        if (root) {
         while (root.available())                   // Lee del archivo hasta que ya no haya nada en el.
          {Serial.write(root.read());}
        root.close();}  // close the file:
        
       else {
       Serial.println("error opening test.txt");    // Si el archivo no se abre se imprime un error.
            }
        }
     }
   }
   


void printDirectory(File dir, int numTabs) {       // Desplega en el puerto serial el contenido de la SD.
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
