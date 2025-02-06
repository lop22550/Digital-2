/*
 * UART9600.c
 *
 * Created: 5/02/2025 10:47:22
 *  Author: bjosu
 */ 

#include <avr/io.h>

void initUART9600(void){
	
	DDRD &= ~(1<<PORTD0);		//Entrada RX
	DDRD |= (1<<PORTD1);		//Salida TX
	
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	UCSR0A |= (1<<U2X0);	//Configurar A Modo Fast U2X0 = 1
	
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);	//Configurar B > Habilitar ISR RX, Habilitarmos RX y TX
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);		//Configurar C > Frame: 8 bits de datos, no paridad, 1 bit de stop
	
	UBRR0 = 207; //Usando un Baudrate de 9600
}