/*
 * main.c
 *
 * Created: 2/13/2025 11:44:19 AM
 *  Author: bjosu
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "I2C/I2C.h"
#include "LCD/LCD.h"

#define CERO 48

#define slave1 0x30
#define slave2 0x40

uint8_t direccion;
uint8_t temp;
uint8_t bufferI2C;
uint8_t valorI2C = 0;

void initPorts(void);
void refreshPORT(uint8_t valor);


int main(void)
{
	I2C_Master_Init(100000,1); // inicializar como Master Fscl 100kHz, prescaler 1
	//initPorts();
	initLCD8bits();
	LCD_Set_Cursor(7,1);
	_delay_ms(1);
	LCD_Write_Char('S'); LCD_Write_Char('2');
	
	while (1)
	{
		
		PORTB |=(1<<PORTB5);
		
		I2C_Master_Start();
		// Escritura
		bufferI2C = slave1 << 1 & 0b11111110;
		
		temp = I2C_Master_Write(bufferI2C);
		if(temp != 1){
			I2C_Master_Stop();
		}
		I2C_Master_Write('R');
		I2C_Master_Stop();
		_delay_ms(500);
		
		PORTB &=~(1<<PORTB5);
		I2C_Master_Start();
		// Lectura
		bufferI2C = slave1 << 1 | 0b00000001;
		
		temp = I2C_Master_Write(bufferI2C);
		if(temp != 1){
			I2C_Master_Stop();
		}
		
		TWCR = (1<<TWINT)|(1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
		
		valorI2C= TWDR;
		
		I2C_Master_Stop();
		
		LCD_Set_Cursor(7,2);
		//LCD_Write_Char(valorI2C);
		//refreshPORT(valorI2C);
		ConvertADC(valorI2C);
		
		
		_delay_ms(500);
	}
}

void initPorts(void){
	// Salidas
	DDRC |= (1<< DDC0)|(1<< DDC1)|(1<< DDC2)|(1<< DDC3);
	DDRD |= (1<< DDD2)|(1<< DDD3)|(1<< DDD4)|(1<< DDD5);
	refreshPORT(0);
	DDRB |= (1<<DDB5);
	
}
void refreshPORT(uint8_t valor){
	if(valor & 0b10000000){
		PORTD |= (1<<PORTD5);
		}else{
		PORTD &= ~(1<<PORTD5);
	}
	if(valor & 0b01000000){
		PORTD |= (1<<PORTD4);
		}else{
		PORTD &= ~(1<<PORTD4);
	}
	if(valor & 0b00100000){
		PORTD |= (1<<PORTD3);
		}else{
		PORTD &= ~(1<<PORTD3);
	}
	if(valor & 0b00010000){
		PORTD |= (1<<PORTD2);
		}else{
		PORTD &= ~(1<<PORTD2);
	}
	if(valor & 0b00001000){
		PORTC |= (1<<PORTC3);
		}else{
		PORTC &= ~(1<<PORTC3);
	}
	if(valor & 0b00000100){
		PORTC |= (1<<PORTC2);
		}else{
		PORTC &= ~(1<<PORTC2);
	}
	if(valor & 0b00000010){
		PORTC |= (1<<PORTC1);
		}else{
		PORTC &= ~(1<<PORTC1);
	}
	if(valor & 0b00000001){
		PORTC |= (1<<PORTC0);
		}else{
		PORTC &= ~(1<<PORTC0);
	}
	
}

void ConvertADC(uint8_t conversionADC){
	uint8_t unidades, decenas, centenas;
	
	unidades = conversionADC % 10;						//ej. 156 %10 = 6
	conversionADC = (conversionADC - unidades)/10;		//(156-6)/10 = 150/10 = 15
	decenas = conversionADC % 10;						//15%10 = 5
	conversionADC = (conversionADC - decenas)/10;		//(15-5)/10 = 1
	centenas = conversionADC % 10;						//1%10 = 1
	
	_delay_ms(100);

	LCD_Write_Char(CERO + centenas);
	LCD_Write_Char(CERO + decenas);
	LCD_Write_Char(CERO + unidades);
	
	
}
