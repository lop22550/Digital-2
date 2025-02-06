/*
 * Universidad del Valle de Guatemala 
 * Electrónica digital 2
 * Sección 10
 * Created: 1/30/2025 1:25:54 PM
 *  Author: Boris Josué López Moreira
 * Carné 22550
 */ 

#define CERO 48
#define UNO 49
#define DOS 50

#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>




uint8_t valor_adc = 0;
volatile char bufferRX;
char cadena[];

#include "LCD/LCD.h"

int main(void)
{
	initADC();
	initLCD8bits();
		_delay_ms(2);
	LCD_Set_Cursor(0,1);
	
	_delay_ms(1);
	LCD_Write_Char('H');
	LCD_Write_Char('O');
	LCD_Write_Char('L');
	LCD_Write_Char('A');

		_delay_ms(2);	
	LCD_Set_Cursor(1,2);
		_delay_ms(2);
	LCD_Write_String(cadena);

    while(1)
    {
		

        //TODO:: Please write your application code 
    }
}


void ConvertADC(uint8_t conversionADC){
	uint8_t unidades, decenas, centenas;
	
	unidades = conversionADC % 10;						//ej. 156 %10 = 6
	conversionADC = (conversionADC - unidades)/10;		//(156-6)/10 = 150/10 = 15
	decenas = conversionADC % 10;						//15%10 = 5
	conversionADC = (conversionADC - decenas)/10;		//(15-5)/10 = 1
	centenas = conversionADC % 10;						//1%10 = 1
	
	_delay_ms(3);
	LCD_Set_Cursor(0, 2);
	LCD_Write_Char(CERO + unidades);
	LCD_Write_Char(CERO + decenas);
	LCD_Write_Char(CERO + centenas);
}


ISR (ADC_vect){
	valor_adc = ADCH; // 1010 1110 & 0000 1111
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
}


ISR(USART_RX_vect){
	bufferRX = UDR0;

		
	}
