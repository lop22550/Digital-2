/*
 * Universidad del Valle de Guatemala
 * Electr�nica Digital 2
 * Archivo: Laboratorio 4
 * Hardware: ATMega328p
 * Autor: Adriana Marcela Gonzalez, Boris Josu� L�pez Moreira
 * Carnet: 22438, 22550
 */ 

/*
 * Este c�digo es para comunicar con el sensor de humedad DHT11 y enviar su lectura al MCU Master mediante 
 * comunicaci�n I2C.
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C/I2C.h"
#include "PWM/PWM.h"

//C�digo del esclavo del sensor de humedad. 
#define SlaveAddress 0x30


uint8_t buffer = 0;  //Almacena los valores enviados por I2C
volatile uint64_t valorDH11 = 0; // Se almacena el valor completo de la lectura del sensor (n�tese el tama�o de la variable).
volatile uint8_t DHT11_data[5];  // Estructuras para guardar cada Byte de la lectura. 

//Variables para almacenar las lecturas enviadas por el sensor DHT11.
uint8_t Humedad_entero = 0;
volatile uint8_t Humedad_decimal = 0;
volatile uint8_t Temperatura_entero = 0;
volatile uint8_t Temperatura_decimal = 0;

uint8_t angle = 0;  //Variable para�enviar un valor de �ngulo.

void DHT11_Request(void);   //Funci�n que inicia la comunicaci�n con el sensor
void DHT11_Response(void);  //Funci�n para cambiar el pin de salida por entrada. 
uint8_t DHT11_ReadByte();   //Funci�n para leer bytes
void DHT11_Read(void);      //Funci�n de lectura
//uint8_t mapServoAngle(angle);
//void Servo_SetAngle(uint8_t angle);
//void initPWM1();

void servo_set_angle(uint8_t angle); //Funci�n para setear �ngulo del servo


int main(void)
{
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);

	
	
	DDRC |= (1<<DDC1);
	PORTC &= ~(1<<PORTC1);
	//initPorts();
	
	I2C_Slave_Init(SlaveAddress);	
	
	//Configuraci�n de Timer 1 (Prescaler 8 = 2MHz)
	TCCR1B |= (1 << CS11); // Prescaler 8
	TCNT1 = 0; // Inicia en 0
	
	// Configuraci�n PWM para servo (Timer1, Fast PWM, 50 Hz)
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	ICR1 = 20000; // 20 ms (50 Hz)
	
	//initServoPWM();

		
		
	sei();		// Habilitar Interrupciones
	
	while (1)
	{
		DHT11_Read();
		_delay_ms(2000);
		
		// Iniciando conversi�n del sensor de humedad DHT11
		Humedad_entero = DHT11_data[0];
		Humedad_decimal = DHT11_data[1];
		Temperatura_entero  = DHT11_data[2];
		Temperatura_decimal = DHT11_data[3];
	
	
	
		//Si el valor de humedad baja del 40%, se enciende el rociador de la planta
		if (Humedad_entero <= 60){
			
			servo_set_angle(0);
			servo_set_angle(45);
			_delay_ms(100);
			servo_set_angle(90);
			_delay_ms(100);
			servo_set_angle(120);
			_delay_ms(100);
			servo_set_angle(180);
			_delay_ms(100);
			servo_set_angle(0);
			
		}
	
		
		// Control del servo seg�n el comando 'riegoON' recibido por I2C
		if (buffer == 'R') {
			/*// Si se recibe el comando 'riegoON', mover el servo
			servo_set_angle(0);
			_delay_ms(500);
			servo_set_angle(180);  // Mover el servo al �ngulo m�ximo
			_delay_ms(500);
			servo_set_angle(0);    // Regresar el servo al �ngulo 0*/
			buffer = 0;            // Limpiar el buffer despu�s de ejecutar
		}
		
		

		
	}
}


//---Funciones-----------------------------------------------------------------------------------------------------------

void servo_set_angle(uint8_t angle) {
	OCR1A = 1000 + (angle * 11.1); // 1000 �s (0�) a 2000 �s (180�)
}



void DHT11_Request(void) {
	DDRC |= (1 << DDC0);  // Configurar PC0 como salida
	PORTC &= ~(1 << PORTC0);  // Enviar se�al baja
	_delay_ms(20);  // Mantener se�al baja al menos 18ms
	PORTC |= (1 << PORTC0);  // Enviar se�al alta
	_delay_us(40);  // Esperar 40us
}

// Configurar el pin como entrada para recibir la respuesta
void DHT11_Response() {
	DDRC &= ~(1 << DDC0);  // Configurar PD2 como entrada
	while (PINC & (1 << PINC0));
	while (!(PINC & (1 << PINC0)));  // Esperar a que el sensor env�e HIGH
	while (PINC & (1 << PINC0));  // Esperar a que termine la respuesta
}

// Leer un byte del DHT11
uint8_t DHT11_ReadByte() {
	uint8_t i, data = 0;
	for (i = 0; i < 8; i++) {
		while (!(PINC & (1 << PINC0)));  // Esperar a que el pin sea HIGH
		_delay_us(31);  // Esperar 30us
		if (PINC & (1 << PINC0))  // Si el pin sigue en HIGH despu�s de 30us, es un "1"
		data = (data << 1) | 1;
		else
		data = (data << 1);
		while (PINC & (1 << PINC0));  // Esperar a que el pin vuelva a LOW
	}
	return data;
}

// Funci�n para leer el sensor
void DHT11_Read(void) {
	DHT11_Request();
	DHT11_Response();
 
	// Leer 5 bytes de datos
	DHT11_data[0] = DHT11_ReadByte();  // Humedad entera
	DHT11_data[1] = DHT11_ReadByte();  // Humedad decimal
	DHT11_data[2] = DHT11_ReadByte();  // Temperatura entera
	DHT11_data[3] = DHT11_ReadByte();  // Temperatura decimal
	DHT11_data[4] = DHT11_ReadByte();  // Checksum

	// Verificar checksum
	if (((DHT11_data[0] + DHT11_data[1] + DHT11_data[2] + DHT11_data[3]) &0xFF) == DHT11_data[4]){
	// Datos v�lidos
	   PORTC |= (1<<PORTC1);
	   valorDH11 =  1;
	}  
	else{ // Error en la transmisi�n
		PORTC &= ~(1<<PORTC1);
	    valorDH11= 0;
		}  
	

}





//---Interrupciones------------------------------------------------------------------------------------------
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
		TWDR = Humedad_entero; // Cargar el dato
		TWCR = (1 << TWEN)|(1 << TWIE)|(1 << TWINT)|(1 << TWEA); // Inicia el envio
		break;
		default: // Se libera el bus de cualquier error
		TWCR |= (1<< TWINT)|(1<<TWSTO);
		break;
	}
}
