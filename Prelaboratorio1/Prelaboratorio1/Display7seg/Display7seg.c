/*
 * Display7seg.c
 *
 * Created: 23/01/2025 10:47:58
 *  Author: bjosu
 */ 
#include <avr/io.h>
#include <stdint.h>

#include "Display7seg.h"


//Función para inicializar pines para display
void initDisplay(void){
	//Los pines a utilizar son los pines D0-D7
	UCSR0B  &= ~(1<<RXEN0); //Deshabilitar los puertos de comunicación
	UCSR0B  &= ~(1<<TXEN0);
	DDRD = 0b11111111; //Los pines D como salida
	
	
}

//Función para desplegar un número
void displayNum(uint8_t numero){

	switch(numero){
		case 0:
		 PORTD |= (1<<PORTD0);
		 PORTD |= (1<<PORTD1);
		 PORTD |= (1<<PORTD2);
		 PORTD |= (1<<PORTD3);
		 PORTD |= (1<<PORTD4);
		 PORTD |= (1<<PORTD5);
		 PORTD &= ~(1<<PORTD6);
		 
		break;
		case 1:
		PORTD &= ~(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD &= ~(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD &= ~(1<<PORTD5);
		PORTD &= ~(1<<PORTD6);
		//PORTD = 0b0000110;
		
		
		break;
		case 2:
		PORTD |= (1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD &= ~(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD |=(1<<PORTD4);
		PORTD &= ~(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		
		break;
		case 3:
		PORTD |=(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD &= ~(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		
		break;
		case 4:
		PORTD &= ~(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD &= ~(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD |=(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		
		break;
		case 5:
		/*PORTD |=(1<<PORTD0);
		PORTD &= ~(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD |=(1<<PORTD5);
		PORTD |=(1<<PORTD6);*/
		PORTD = 0b1101101;
		
		break;
		case 6:
		PORTD |=(1<<PORTD0);
		PORTD &= ~(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD |=(1<<PORTD4);
		PORTD |=(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		
		break;
		case 7:
		PORTD |=(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD &= ~(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD &= ~(1<<PORTD5);
		PORTD &= ~(1<<PORTD6);
		
		break;
		case 8:
		PORTD |=(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD |=(1<<PORTD4);
		PORTD |=(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		PORTD |=(1<<PORTD7);
		break;
		case 9:
		PORTD |=(1<<PORTD0);
		PORTD |=(1<<PORTD1);
		PORTD |=(1<<PORTD2);
		PORTD |=(1<<PORTD3);
		PORTD &= ~(1<<PORTD4);
		PORTD |=(1<<PORTD5);
		PORTD |=(1<<PORTD6);
		
		break;
		default: PORTD = 0b00000000;
	}
	
}

//Función para desplegar el punto
void displayP(uint8_t punto){
	PORTD = 0b10000000;
	
}