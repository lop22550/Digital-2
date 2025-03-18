#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>    // Incluye la biblioteca de entrada/salida AVR
#include <stdint.h>    // Incluye la biblioteca de tipos de datos est�ndar enteros

#define invertido 1       // Definici�n de la constante para configuraci�n invertida
#define no_invertido 0   // Definici�n de la constante para configuraci�n no invertida

#define PWM_TOP 311
#define MIN1 9
#define MAX1 30

// Declaraci�n de las funciones para el control del PWM en el canal A del Timer 0
void initPWM0FastA(uint8_t inverted, uint16_t precaler);
void updateDCA(uint8_t duty);

// Declaraci�n de las funciones para el control del PWM en el canal B del Timer 0
void initPWM0FastB(uint8_t inverted, uint16_t precaler);
void updateDCB(uint8_t duty);


void initServoPWM();
void setServoAngle(uint8_t angle);

void initPWM1A (void);
void updateDutyCycleA1(uint8_t angulo);

#endif /* PWM_H_ */