/*
 * LCD.h
 *
 * Created: 30/01/2025 13:44:29
 *  Author: bjosu
 */ 


#ifndef LCD_H_
#define LCD_H_

#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>
#include <string.h>



/*
 * PUERTOS UTILIZADOS DEL ARDUINO NANO
 * Nombre del puerto = puerto del LCD
 * D2 = RS
 * D3 = RW 
 * D4 = E
 * D5 = D0
 * D6 = D1
 * D7 = D2
 * B0 = D3
 * B1 = D4
 * B2 = D5
 * B3 = D6
 * B4 = D7
 */



void initLCD4bits (void);
void initLCD8bits(void);
void LCD_Port (char a);
void LCD_CMD(char a);
void LCD_Write_Char(char caracter);
void LCD_Write_String(char *a);
void LCD_Shift_Right(void);
void LCD_Shift_Left(void);
void LCD_Set_Cursor(int columna, int fila);


#endif /* LCD_H_ */