/*
 * Universidad del Valle de Guatemala 
 * Boris Josué López Moreira
 * Carné 22550
 * Electrónica digital 2 
 * Sección 11
 * Created: 2/6/2025 4:37:03 PM
 */ 
#define F_CPU 16000000UL
#define CERO 48
#define UNO 49
#define DOS 50


#include <avr/io.h>
#include <util/delay.h> 
#include "ADC/ADC.h"
#include "SPI/SPI.h"
#include <avr/interrupt.h>

uint8_t valorSPI = 0;
uint8_t valor_adc = 0; 
uint8_t conversionADC = 0;				//Esta variable la usaré para convertir la lectura en ADC en un valor char que pueda mostrarse en la terminal
uint8_t bufferRX = 0;
uint8_t spiValor = 0;

void initUART9600 (void);				//Función donde se configura la comunicación serial UART
void writeUART(char caracter);
void writeTextUART(char* texto);
void ConvertADC (uint8_t lectura_ADC);
void refreshPORT(uint8_t valor);


int main(void)
{ 
	cli();
	
	//Programación para MAESTRO
	
	
	initADC();
	initUART9600();
	DDRD |= ((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTD = 0;	
	DDRB |= ((1<<DDB0)|(1<<DDB1));
	PORTB &= ~((1<<PORTB0)|(1<<PORTB1));
	spiInit(SPI_MASTER_OSC_DIV16, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	//spiInit(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	SPCR |= (1<<SPIE);
	
	sei();
	 ADCSRA |= (1 << ADSC);
	 
    while(1)
    {
		
		PORTB &= ~(1<<PORTB2);  //SLAVE SELECT
		spiWrite(bufferRX);
	
		refreshPORT(bufferRX);
		//refreshPORT(spiValor);
		
		//PORTB |= (1<<PORTB2);    //SLAVE SELECT

		 _delay_ms(100);  // Delay para observar los LEDs
	

    }
	
	//Programación para ESCLAVO
	/*DDRC |= (1<<DDC1)|(1<<DDC2)|(1<<DDC3)|(1<<DDC4)|(1<<DDC5);
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4);
	PORTC &= ~((1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3)|(1<<PORTC4)|(1<<PORTC5));
	PORTD &= ~((1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4));
	
	spiInit(SPI_SLAVE_SS,SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	initADC();
	refreshPORT(spiValor);
	SPCR |= (1<<SPIE); */
	
}

void refreshPORT(uint8_t valor){
	if(valor & 0b10000000){
		PORTB |= (1<<PORTB1);
	}else {
		PORTB &= ~(1<<PORTB1);
	}
	
	if(valor & 0b01000000){
		PORTB |= (1<<PORTB0);
		}else {
		PORTB &= ~(1<<PORTB0);
	}
	
	if(valor & 0b00100000){
		PORTD |= (1<<PORTD7);
		}else {
		PORTD &= ~(1<<PORTD7);
	}
	
	if(valor & 0b00010000){
		PORTD |= (1<<PORTD6);
		}else {
		PORTD &= ~(1<<PORTD6);
	}
	
	if(valor & 0b00001000){
		PORTD |= (1<<PORTD5);
		}else {
		PORTD &= ~(1<<PORTD5);
	}
	
	if(valor & 0b00000100){
		PORTD |= (1<<PORTD4);
		}else {
		PORTD &= ~(1<<PORTD4);
	}
	
	if(valor & 0b00000010){
		PORTD |= (1<<PORTD3);
		}else {
		PORTD &= ~(1<<PORTD3);
	}
	
	if(valor & 0b00000001){
		PORTD |= (1<<PORTD2);
		}else {
		PORTD &= ~(1<<PORTD2);
	}
}
void initUART9600(void){
	DDRD &= ~(1<<DDD0);		//Entrada RX
	DDRD |= (1<<DDD1);		//Salida TX
	
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	UCSR0A |= (1<<U2X0);	//Configurar A Modo Fast U2X0 = 1
	
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);	//Configurar B > Habilitar ISR RX, Habilitarmos RX y TX
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);		//Configurar C > Frame: 8 bits de datos, no paridad, 1 bit de stop
	
	UBRR0 = 207; //Usando un Baudrate de 9600
}

//Función de transmisión UART
void writeUART(char caracter) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = caracter;
}

void writeTextUART(char* texto) {
	uint8_t i;
	for (i = 0; texto[i]!= '\0'; i++){
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = texto[i];
	}
}	

void ConvertADC(uint8_t conversionADC){
	uint8_t unidades, decenas, centenas;
	
	unidades = conversionADC % 10;						//ej. 156 %10 = 6
	conversionADC = (conversionADC - unidades)/10;		//(156-6)/10 = 150/10 = 15
	decenas = conversionADC % 10;						//15%10 = 5
	conversionADC = (conversionADC - decenas)/10;		//(15-5)/10 = 1
	centenas = conversionADC % 10;						//1%10 = 1
	
	_delay_ms(1000);
	writeUART(CERO + centenas);
	writeUART(CERO + decenas);
	writeUART(CERO + unidades);
	
	
	writeUART('\n');
	//writeUART('\r');
}


ISR (ADC_vect){
	
	valor_adc = ADCH; 
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1 << ADSC);
}


ISR (SPI_STC_vect){
	spiValor = SPDR;
}


ISR (USART_RX_vect){
	bufferRX = UDR0;

}