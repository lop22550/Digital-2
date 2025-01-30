/*
 * Display7seg.h
 *
 * Created: 23/01/2025 10:48:18
 *  Author: bjosu
 */ 


#ifndef DISPLAY7SEG_H_
#define DISPLAY7SEG_H_

#include <stdint.h>

//Función para inicializar pines para display
void initDisplay(void);

//Función para desplegar un número
void displayNum(uint8_t numero);

//Función para desplegar el punto
void displayP(uint8_t punto);





#endif  /*DISPLAY7SEG_H_ */