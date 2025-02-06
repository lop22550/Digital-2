/*
 * Universidad del Valle de Guatemala 
 * Electrónica digital 2
 * Sección 10
 * Created: 1/30/2025 1:25:54 PM
 *  Author: Boris Josué López Moreira
 * Carné 22550
 */ 


#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


uint8_t valor_adc = 0;
volatile char bufferRX;


#include "LCD/LCD.h"

int main(void)
{
	//initADC();
	initLCD8bits();
	//initLCD4bits();
	_delay_ms(3);	
	//LCD_Set_Cursor(1,1);
	//_delay_ms(3);
	LCD_Write_Char('H');
	LCD_Write_Char('O');
	LCD_Write_Char('L');
	LCD_Write_Char('A');


	/*LCD_Write_Char('H');
	LCD_Write_Char('H');
	LCD_Write_Char('H');
	LCD_Set_Cursor(1, 2);*/
	//LCD_Write_String('MUNDO');
    while(1)
    {
		

        //TODO:: Please write your application code 
    }
}



ISR (ADC_vect){
	/*PORTB &= ~(1<<PB0); //Se apagan los LEDS del contador binario
	PORTB |= (1<<PB1);	//Se encienden los displays de 7 segmentos de unidades.
	PORTB |= (1<<PB2);*/
	
	//uint8_t 
	valor_adc = ADCH; // 1010 1110 & 0000 1111
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
}


ISR(USART_RX_vect){
	bufferRX = UDR0;
	
	

		
		//while (!(UCSR0A & (1<<UDRE0)));
		//UDR0 = bufferRX;
		
	}
