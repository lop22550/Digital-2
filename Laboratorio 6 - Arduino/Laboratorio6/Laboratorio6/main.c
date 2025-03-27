/*
 * Universidad del Valle de Guatemala 
 * Electrónica digital 2
 * Hardware: ATMega328P
 * Created: 3/20/2025 8:12:01 PM
 *  Author: Boris Josué López Moreira
 * Carné: 22550
 */ 
//***************************
#define F_CPU 16000000

// Librerías incluidas a lo largo del programa
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEBOUNCE_TIME 25 // Tiempo de delay para el anti-rrebote

//***************************
// Prototipos de función
//***************************
void initPorts(void); // Función para iniciar puertos 
void initUART9600(void);
void writeUART(char caracter);
void writeTextUART(char* texto);
//***************************
// Variables globales
//***************************
uint8_t flag_up = 0; 
uint8_t flag_down = 0;
uint8_t flag_left = 0;
uint8_t flag_right = 0;
uint8_t flag_A = 0;
uint8_t flag_B = 0;


//***************************
// Código principal
//***************************

int main(void) {
    initPorts();
	initUART9600();
    writeUART(48);
    // Habilitar las interrupciones globales
    sei();
    
    while (1) {
		if (flag_up == 1){
			writeUART('u');
			flag_up = 0;
		}
		
		if (flag_down == 1){
			writeUART('d');
			flag_down = 0;
		}
		
		if (flag_left == 1){
			writeUART('l');
			flag_left = 0;
		}
		
		if (flag_right == 1){
			writeUART('r');
			flag_right = 0;
		}
		
		if (flag_A == 1){
			writeUART('A');
			flag_A = 0;
		}
		
		if (flag_B == 1){
			writeUART('B');
			flag_B = 0;
		}
    }
}

//***************************
// Subrutinas
//***************************
void initPorts(void) {
    // Configurar botones como entradas
	DDRD &= ~(1 << DDD2);
	DDRD &= ~(1 << DDD3);
	DDRD &= ~(1 << DDD4);
	DDRD &= ~(1 << DDD5);
	DDRD &= ~(1 << DDD6);
	DDRD &= ~(1 << DDD7);
	
    // Habilitar pull-up en los botones
    PORTD |= (1 << DDD2);
	PORTD |= (1 << DDD3);
	PORTD |= (1 << DDD4);
	PORTD |= (1 << DDD5);
	PORTD |= (1 << DDD6);
	PORTD |= (1 << DDD7);
    
    // Habilitar ISR para PB4, PC4 y PD7
    PCICR |= (1 << PCIE0) | (1 << PCIE1) | (1 << PCIE2);
    
    // Habilitar los botones para que funcionen con la interrupción
	PCMSK2 |= ((1 << PCINT23)| (1 << PCINT22)| (1 << PCINT21)| (1 << PCINT20)| (1 << PCINT19)| (1 << PCINT18));
    
   
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



//***************************
// ISR
//***************************

// Interrupción para el botón rojo 
ISR(PCINT2_vect) {
        if (!(PIND & (1 << PIND2))) {  // Botón del jugador rojo
	        _delay_ms(DEBOUNCE_TIME); // Anti-rrebote
	        if (!(PIND & (1 << PIND2))){
		        flag_up = 1;
	        }
        }
		
		
		if (!(PIND & (1 << PIND3))) {  // Botón del jugador rojo
	        _delay_ms(DEBOUNCE_TIME); // Anti-rrebote
	        if (!(PIND & (1 << PIND3))){
		        flag_down = 1;
	        }
        }
		
		if (!(PIND & (1 << PIND4))) {  // Botón del jugador rojo
			_delay_ms(DEBOUNCE_TIME); // Anti-rrebote
			if (!(PIND & (1 << PIND4))){
				flag_left = 1;
			}
		}
		
		if (!(PIND & (1 << PIND5))) {  // Botón del jugador rojo
			_delay_ms(DEBOUNCE_TIME); // Anti-rrebote
			if (!(PIND & (1 << PIND5))){
				flag_right = 1;
			}
		}
		
		if (!(PIND & (1 << PIND6))) {  // Botón del jugador rojo
			_delay_ms(DEBOUNCE_TIME); // Anti-rrebote
			if (!(PIND & (1 << PIND6))){
				flag_A = 1;
			}
		}
		
		if (!(PIND & (1 << PIND7))) {  // Botón del jugador rojo
			_delay_ms(DEBOUNCE_TIME); // Anti-rrebote
			if (!(PIND & (1 << PIND7))){
			 flag_B = 1;
		  }
		}
    
	}

