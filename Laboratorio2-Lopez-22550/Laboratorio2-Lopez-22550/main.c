/*
 * Universidad del Valle de Guatemala 
 * Electr�nica digital 2
 * Secci�n 10
 * Created: 1/30/2025 1:25:54 PM
 *  Author: Boris Josu� L�pez Moreira
 * Carn� 22550
 */ 


#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>

#include "LCD/LCD.h"

int main(void)
{
	
	initLCD8bits();
	LCD_Write_Char('H');
	LCD_Write_String('MUNDO');
    while(1)
    {
		
		
        //TODO:: Please write your application code 
    }
}