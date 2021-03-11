#ifndef _OSCILADOR_H
#define	_OSCILADOR_H

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)

#include <xc.h> // include processor files - each processor file is guarded.  

//**********************
// Prototipo de la función para inicializar Oscilador Interno
// Parametros: Opción de frecuencia a utilizar ver pág. 62 Manual
//**********************
void InitOSC(uint8_t frec);

#endif	/_OSCILADOR_H/