#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>    // Incluye la biblioteca de entrada/salida AVR
#include <stdint.h>    // Incluye la biblioteca de tipos de datos estándar enteros

#define invertido 1       // Definición de la constante para configuración invertida
#define no_invertido 0   // Definición de la constante para configuración no invertida

#define PWM_TOP 311
#define MIN1 9
#define MAX1 30

// Declaración de las funciones para el control del PWM en el canal A del Timer 0
void initPWM0FastA(uint8_t inverted, uint16_t precaler);
void updateDCA(uint8_t duty);

// Declaración de las funciones para el control del PWM en el canal B del Timer 0
void initPWM0FastB(uint8_t inverted, uint16_t precaler);
void updateDCB(uint8_t duty);


void initServoPWM();
void setServoAngle(uint8_t angle);

void initPWM1A (void);
void updateDutyCycleA1(uint8_t angulo);

#endif /* PWM_H_ */