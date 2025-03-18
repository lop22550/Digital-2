//***************************
// Universidad del Valle de Guatemala
// Electrónica Digital 2
// Archivo: Laboratorio 4 
// Hardware: ATMega328p
// Autor: Adriana Marcela Gonzalez, Boris Josué López Moreira 
// Carnet: 22438, 22550
//***************************
// Librerías
//***************************
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C/I2C.h"

#define SlaveAddress 0x30

uint8_t buffer = 0;
volatile uint8_t valorADC = 0;


void initPorts(void);
void refreshPORT(uint8_t valor);
void initADC(void);
void ConvertADC (uint8_t lectura_ADC);


int main(void)
{
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	initPorts();
	initADC();
	
	I2C_Slave_Init(SlaveAddress);
	
	sei();		// Habilitar Interrupciones
	
	while (1)
	{
		// Iniciando secuencia de adc
		ADCSRA |= (1<< ADSC);
		_delay_ms(100);
		refreshPORT(valorADC);
		if(buffer == 'R'){
			PINB |= (1<<PINB5);
			buffer = 0;
		}
		
	}
}
void initADC(void){
	ADMUX = 0;
	
	// Vref = AVCC = 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	// Justificando hacia la izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA = 0;
	//Encendiendo ADC
	ADCSRA |= (1<<ADEN);
	
	// Habilitamos ISR ADC
	ADCSRA |= (1<<ADIE);
	
	// Prescaler de 128 > 16M / 128 = 125kHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	// Deshabilitando la intrada digital PC0
	DIDR0 |= (1<<ADC0D);
	
}

ISR(ADC_vect){
	valorADC = ADCH;
	ADCSRA |= (1<<ADIF);
}

ISR(TWI_vect){
	uint8_t estado;
	estado = TWSR & 0xFC;
	switch(estado){
		case 0x60:
		case 0x70:
		TWCR |= (1<< TWINT);
		break;
		case 0x80:
		case 0x90:
		buffer = TWDR;
		TWCR |= (1<< TWINT); // Se limpia la bandera
		break;
		case 0xA8:
		case 0xB8:
		TWDR = valorADC; // Cargar el dato
		TWCR = (1 << TWEN)|(1 << TWIE)|(1 << TWINT)|(1 << TWEA); // Inicia el envio
		break;
		default: // Se libera el bus de cualquier error
		TWCR |= (1<< TWINT)|(1<<TWSTO);
		break;
	}
}


void initPorts(void){
	// Salidas
	DDRC |= (1<< DDC1)|(1<< DDC2)|(1<< DDC3);
	DDRD |= (1<< DDD2)|(1<< DDD3)|(1<< DDD4)|(1<< DDD5)|(1<< DDD6);
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
		PORTD |= (1<<PORTD6);
		}else{
		PORTD &= ~(1<<PORTD6);
	}
	
}