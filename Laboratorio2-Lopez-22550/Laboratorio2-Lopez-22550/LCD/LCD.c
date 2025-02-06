/*
 * LCD.c
 *
 * Created: 30/01/2025 13:44:21
 *  Author: bjosu
 */ 

#include "LCD.h"


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

void initLCD8bits(void){
	//Configurar los puertos como salidas 
	DDRD |= ((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTD &= ~((1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5)|(1<<PORTD6)|(1<<PORTD7));
	
	DDRB |= ((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5));
	PORTB = 0;
	
	//Power on
	LCD_Port(0x00);
	//Pause 15 ms
	_delay_ms(20);
	//Function set
	LCD_CMD(0x38);
	//Pause 100us
	_delay_us(110);

	//Display on/off
	LCD_CMD(0x0C);
	//Pause 100us
	_delay_us(110);
	//Entry mode
	LCD_CMD(0x06);
	//Pause 100us
	_delay_us(110);
	//Clear display
	LCD_CMD(0x01);
	
	
	
}
void initLCD4bits(void){
	
	//Ejemplo de Pablo 
	
	DDRC |= ((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC3)|(1<<DDC4));
	PORTC = 0;
	
	LCD_Port(0x00);
	_delay_ms(20);
	LCD_CMD(0x03);
	_delay_ms(5);
	LCD_CMD(0x03);
	_delay_ms(11);
	LCD_CMD(0x03);
	
	LCD_CMD(0x02);
	
	//////////
	// Funcion Set
	LCD_CMD(0x02);
	LCD_CMD(0x08);
	
	//Display ON/OFF
	LCD_CMD(0x00);
	LCD_CMD(0x0C);
	
	// Entry Mode 
	LCD_CMD(0x00);
	LCD_CMD(0x06);
	
	//Clear display 
	LCD_CMD(0x00);
	LCD_CMD(0x01);
	
}
//Función para enviar un comando
void LCD_CMD(char a){
		//RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
		PORTD &= ~(1<<PORTD2);
		LCD_Port(a);
		//EN = 1;  // => E = 1
		PORTD |= (1<<PORTD4);
		_delay_ms(4);
		//EN = 0; // => E = 0
		PORTD &= ~(1<<PORTD4);
		
		/* EJEMPLO PABLO
		//RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
		PORTC &= ~(1<<PORTC0);
		LCD_Port(a);
		//EN = 1;  // => E = 1
		PORTC |= (1<<PORTC1);
		_delay_ms(4);
		//EN = 0; // => E = 0
		PORTC &= ~(1<<PORTC1);*/
		
		
}

//Función para colocar en el puerto un valor
void LCD_Port(char a){
	if (a & 1)
	PORTD |= (1<<PORTD5);  //D0 = 1
	else
	PORTD &= ~(1<<PORTD5); //D0 = 0
	
	
	
	if (a & 2)
	PORTD |= (1<<PORTD6); //D1 = 1
	else
	PORTD &= ~(1<<PORTD6); //D1 = 0
	
	
	
	if (a & 4)
	PORTD |= (1<<PORTD7);//D2 = 1
	else
	PORTD &= ~(1<<PORTD7); //D2 = 0
	
	
	
	if (a & 8)
	PORTB |= (1<<PORTB0); //D3 = 1
	else 
	PORTB &= ~(1<<PORTB0); //D3 = 0
	
	
	if (a & 16)
	PORTB |= (1<<PORTB1); //D4 = 1
	else
	PORTB &= ~(1<<PORTB1); //D4 = 0
	
	
	if (a & 32)
	PORTB |= (1<<PORTB2); //D5 = 1
	else
	PORTB &= ~(1<<PORTB2); //D5 = 0
	
	
	if (a & 64)
	PORTB |= (1<<PORTB3); //D6 = 1
	else
	PORTB &= ~(1<<PORTB3); //D6 = 0
	
	
	if (a & 128)
	PORTB |= (1<<PORTB4); //D7 = 1
	else
	PORTB &= ~(1<<PORTB4); //D7 = 0
	
	
	/*EJEMPLO PABLO
	if (a & 1)
	PORTC |= (1<<PORTC2);  //D0 = 1
	else
	PORTC &= ~(1<<PORTC2); //D0 = 0
	
	
	
	if (a & 2)
	PORTC |= (1<<PORTC3); //D1 = 1
	else
	PORTC &= ~(1<<PORTC3); //D1 = 0
	
	
	
	if (a & 4)
	PORTC |= (1<<PORTC4);//D2 = 1
	else
	PORTC &= ~(1<<PORTC4); //D2 = 0
	
	
	
	if (a & 8)
	PORTC |= (1<<PORTC5); //D3 = 1
	else
	PORTC &= ~(1<<PORTC5); //D3 = 0*/
	
}



//Función para enviar un caracter
void LCD_Write_Char(char caracter){
	//RS = 1; => RS = 1  El dato en el puerto lo va a interpretar como CARACTER (DATO)
	PORTD |= (1<<PORTD2);
	LCD_Port(caracter);
	//EN = 1; => E = 1
	PORTD |= (1<<PORTD4);
	_delay_ms(10);
	PORTD &= ~(1<<PORTD4);
	/*
	char Cbajo, Calto;
	Cbajo = caracter & 0x0F;
	Calto = (caracter & 0x0F)>>4;
	
	PORTC |= (1<<PORTC0);
	LCD_Port(Calto);
	PORTC |= (1<<PORTC1);
	_delay_ms(4);
	PORTC &= ~(1<<PORTC1);
	LCD_Port(Cbajo);
	PORTC |= (1<<PORTC1);
	_delay_ms(4);
	PORTC &= ~(1<<PORTC1);*/

}


//Función para enviar una cadena
void LCD_Write_String(char *a){
	int i;
	for (i=0; a[i] != '\0'; i++)
	LCD_Write_Char(a[i]);
}

//Desplazamiento hacia la derecha
void LCD_Shift_Right(void){
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
}

void LCD_Shift_Left(void){
	LCD_CMD(0x01);
	LCD_CMD(0x08);
}

void LCD_Set_Cursor(char caracter, char fila){
	char temp, z, y; 
	if (fila == 1){
		temp = 0x80 + caracter - 1;
		z = temp >> 4;  
		y = temp & 0x0F; 
		LCD_CMD(z);
		LCD_CMD(y); 
	} else if (fila == 2)
	{
		temp = 0xC0 + caracter - 1;
		z = temp >> 4;
		y = temp & 0x0F;
		LCD_CMD(z);
		LCD_CMD(y);
		}
}