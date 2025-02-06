/*
 * ADC.h
 *
 * Created: 4/02/2025 13:17:47
 *  Author: bjosu
 */ 


#ifndef ADC_H_
#define ADC_H_



#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>

void initADC(void);
void ADC_LCD(int valor_ADC);


#endif /* ADC_H_ */