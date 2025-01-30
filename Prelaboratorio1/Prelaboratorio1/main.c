/* Universidad del Valle de Guatemala
   Electrónica digital 2
   Boris López Carné 22550
   Prelaboratorio 1
   Credo: 23/01/2025  10:24
 */ 

//********************************************************************************
//Librerías
//********************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Display7seg/Display7seg.h"
//********************************************************************************
//Prototipos de función
//********************************************************************************
void initPorts(void);
void boton1(uint8_t count1);
void boton2(uint8_t count2);
void conteo_salida (uint8_t salida);


//********************************************************************************
//Variables globales
//********************************************************************************
uint8_t conteoDisplay;
uint8_t allowed; 
uint8_t count1 =0;
uint8_t count2=0; 
uint8_t numero =0;
uint8_t salida = 0;
uint8_t punto = 1;

//********************************************************************************
//Código principal 
//********************************************************************************

int main(void)
{
	initDisplay();
	initPorts();
	
	//habilitar todas las interrupciones GIE
	sei();
	
   while(1)
    {
       if (salida == 1)
       {conteo_salida(salida);
       }
       
		boton1(count1);  //LEDs AZULES
		boton2(count2);  //LEDs ROJOS
    }
}

//********************************************************************************
//Subrutinas
//********************************************************************************

void initPorts(void){
	
	//Definir entradas de botones
	DDRB &= ~(1 << PORTB4); 
	DDRB &= ~(1 << PORTB5);
	DDRC &= ~(1 << PORTC0);
	//Habilitar pull up de botones
	PORTB |= (1 << PORTB4);
	PORTB |= (1 << PORTB5);
	PORTC |= (1 << PORTC0);
	
	//Habilitamos ISR PCINT0 y PCINT1
	PCICR |= (1<<PCIE0);
	PCICR |= (1<<PCIE1);
	//Habilitar el PB4, PB5,PC0 pra que se active PCINT0 y PCINT1
	PCMSK0 |= (1<<PCINT4);
	PCMSK0 |= (1<<PCINT5);
	PCMSK1 |= (1<<PCINT8);
	
	
	//Definir salidas para leds
	DDRC |= (1 << PORTC1);
	DDRC |= (1 << PORTC2);
	DDRC |= (1 << PORTC3);
	DDRC |= (1 << PORTC4);
	
	
	DDRB |= (1 << PORTB0);
	DDRB |= (1 << PORTB1);
	DDRB |= (1 << PORTB2);
	DDRB |= (1 << PORTB3);
	
	
	
	
}

void conteo_salida (uint8_t salida){
	if (salida == 1)
	{
		DDRB = 0b111111;  //Se desactivan botones
		DDRC |= (1 << PORTC0);
		salida = 0;		
		displayNum(5);
		_delay_ms(1000);
		displayNum(4);
		_delay_ms(1000);
		displayNum(3);
		_delay_ms(1000);
		displayNum(2);
		_delay_ms(1000);
		displayNum(1);
		_delay_ms(1000);
		displayNum(0);
		DDRB = 0b001111;  //Se activan botones
		DDRC &= ~(1 << PORTC0);
		
	} else{
		displayP(1);
	}
	
}

void boton1(uint8_t count1){  //LEDs AZULES
	if (count1 > 4)
	{
		count1 = 0;
		PORTB &= ~((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3));
		//PORTD = 0b0000110;  //Se despliega el número 1
		displayNum(1);
		
	}else{
		switch (count1){
		case 0:
		PORTB &= ~((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3));
		break;	
		case 1:
		PORTB |= (1<<PORTB0);
		break;
		case 2:
		PORTB |= ((1<<PORTB0)|(1<<PORTB1));
		break;
		case 3:
		PORTB |= ((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2));
		break;
		case 4:
		PORTB |= ((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3));
		break;
			
		}
	}
}

void boton2(uint8_t count2){  //LEDs ROJOS
	if (count2 == 4)
	{
		count2 = 0;
		displayNum(2);
	}else{
		switch (count2){
			case 0: 
			
			break;
			case 1:
			PORTC |= (1<<PORTC1);
			break;
			case 2:
			PORTC |= (1<<PORTC1);
			PORTC |= (1<<PORTC2);
			break;
			case 3:
			PORTC |= (1<<PORTC1);
			PORTC |= (1<<PORTC2);
			PORTC |= (1<<PORTC3);
			break;
			case 4:
			PORTC |= (1<<PORTC1);
			PORTC |= (1<<PORTC2);
			PORTC |= (1<<PORTC3);
			PORTC |= (1<<PORTC4);
			break;
			
		}
	}
}

//********************************************************************************
//ISR
//********************************************************************************
ISR(PCINT0_vect){
	if (PINB & (1<<PORTB4))    //Es el botón que inicia cada carrera
	{
	}else{
		//Se presiono el botón
		salida = salida+1;
		
	}
	
	if (PINB & (1<<PORTB5))    //Es el botón para el jugador 1 
	{
		}else{
		//Se presiono el botón
		count1 = count1 + 1;
	}
}

ISR(PCINT1_vect){
	if (PINC & (1<<PORTC4))     //Es el botón para el jugador 2
	{
		}else{
		//Se presiono el botón
		count2 = count2 + 1;
	}
	
}