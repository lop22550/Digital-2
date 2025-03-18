/*
 * Universidad del Valle de Guatemala
 * Electrónica Digital 2
 * Archivo: Laboratorio 4
 * Hardware: ATMega328p
 * Autor: Adriana Marcela Gonzalez, Boris Josué López Moreira
 * Carnet: 22438, 22550
 * Created: 2/27/2025 10:50:10 AM
 */ 

/*
 * Este código fue diseñado con el propósito de programar al microcontrolador Maestro del proyecto, el cuál se comunicará por medio de 
 * comunicación I2C con otros dos microcontroladores y un sensor, mostrará los valores recibidos en una pantalla LCD. De igual manera,
 * se comunicará mediante UART con el microcontrolador ESP32 para recibir las señales dadas en la interfaz virtual.
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "I2C/I2C.h"
#include "LCD/LCD.h"

#define CERO 48

#define slave1 0x30 // Código para comunicarse con el sensor de humedad DHT11 
#define slave2 0x40 // Código para comunicarse con el sensor ultrasónico HC-SR04
#define slave3 0x50 // Código para comunicarse con el sensor de temperatura. 
#define LM75_ADDR 0x48

uint8_t direccion;
uint8_t temp;       // Variable temporal 
uint8_t bufferI2C;  // Variable donde se escribe los códigos de la comunicación I2C.
uint8_t valorI2C = 0;  // Variable para guardar cada lectura de I2C de los slaves. 
uint8_t valorI2C_humedad = 0;  // Variable para guardar cada lectura de I2C de los slaves.
uint8_t valorI2C_distancia = 0;

void initPorts(void);
void refreshPORT(uint8_t valor);
float LM75_ReadTemperature();
void initUART9600(void);
void writeUART(char caracter);
//void writeTextUART(char* texto);
void Convert_Value(uint8_t conversionADC);


int main(void)
{
	I2C_Master_Init(100000,1); // inicializar como Master Fscl 100kHz, prescaler 1
	initLCD8bits();
	
	//Configuración de leyenda de pantalla LCD. 
	LCD_Set_Cursor(1,1);
	LCD_Write_Char('S'); LCD_Write_Char('1');
	LCD_Set_Cursor(7,1);
	_delay_ms(1);
	LCD_Write_Char('S'); LCD_Write_Char('2');
	LCD_Set_Cursor(14,1);
	LCD_Write_Char('S'); LCD_Write_Char('3');
	
	while (1)
	{
		 float temperatura = LM75_ReadTemperature();
		 _delay_ms(1000);
		
		//**************** Comunicación con sensor de humedad ****************************************
		//Se enciende LED indicador de comunicación I2C
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
		
		//Se apaga LED indicador de comunicación I2C
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
		
		//Se almacena el valor del buffer en la variable.
		valorI2C= TWDR;
		
		I2C_Master_Stop();
		
		//Se muestra en LCD la lectura del sensor
		LCD_Set_Cursor(7,2);
		//Función que convierte la lectura en valores ASCII para ser mostradas en la pantalla LCD.
		Convert_Value(valorI2C);
		
		
		_delay_ms(50);
		
		
		//**************** Comunicación con sensor ultrasónico ****************************************
		
		_delay_ms(100);
		PORTB |=(1<<PORTB5);
		
		I2C_Master_Start();
		// Escritura
		bufferI2C = slave2 << 1 & 0b11111110;
		
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
		bufferI2C = slave2 << 1 | 0b00000001;
		
		temp = I2C_Master_Write(bufferI2C);
		if(temp != 1){
			I2C_Master_Stop();
		}
		
		TWCR = (1<<TWINT)|(1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
		
		valorI2C= TWDR;
		
		I2C_Master_Stop();
		
		LCD_Set_Cursor(1,2);
		//LCD_Write_Char(valorI2C);
		//refreshPORT(valorI2C);
		Convert_Value(valorI2C);
		
		
		_delay_ms(50);
		
		/****************************************/
		
		
		 LCD_Set_Cursor(14, 2);
		 LCD_Write_Char(CERO + ((int)temperatura / 10));
		 LCD_Write_Char(CERO + ((int)temperatura % 10));
		 LCD_Write_Char('.');
		 LCD_Write_Char(CERO + ((int)(temperatura * 10) % 10));
		 LCD_Write_Char('C');
		 
		 _delay_ms(100);
		 /********** UART ************************************************ */
		 // Enviar datos de temperatura por UART en el formato esperado por el ESP32
		 writeUART('T');  // Etiqueta de temperatura
		 writeUART(':');
		 writeUART(CERO + ((int)temperatura / 10));
		 writeUART(CERO + ((int)temperatura % 10));
		 writeUART('.');
		 writeUART(CERO + ((int)(temperatura * 10) % 10));
		 writeUART(' ');  // Espacio para separar los valores


		 _delay_ms(100);
		 // Enviar datos de humedad por UART
		 writeUART('H');  // Etiqueta de humedad
		 writeUART(':');
		 writeUART(CERO + ((valorI2C_humedad / 10) % 10));
		 writeUART(CERO + (valorI2C_humedad % 10));
		 writeUART('%');  // Porcentaje
		 writeUART(' ');  // Espacio para separar los valores

		 // Enviar datos de nivel por UART
		 writeUART('N');  // Etiqueta de nivel
		 writeUART(':');
		 writeUART(CERO + ((valorI2C_distancia / 10) % 10));
		 writeUART(CERO + (valorI2C_distancia % 10));
		 writeUART('\n');  // Nueva línea para indicar el final de los datos
		 _delay_ms(100);
	 
		 
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

void Convert_Value(uint8_t conversionADC){
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


float LM75_ReadTemperature() {

	uint8_t msb, lsb;
	int16_t temp_raw;
	float temp;

	I2C_Master_Start();
	I2C_Master_Write((LM75_ADDR << 1) | 0); // Dirección + escritura
	I2C_Master_Write(0x00); // Registro de temperatura
	I2C_Master_Stop();

	I2C_Master_Start();
	I2C_Master_Write((LM75_ADDR << 1) | 1); // Dirección + lectura
	I2C_Master_Read(&msb, 1);  // Leer MSB con ACK
	I2C_Master_Read(&lsb, 0);  // Leer LSB con NACK
	I2C_Master_Stop();

	temp_raw = (msb << 8) | lsb; // Unir los dos bytes
	temp_raw >>= 7; // Solo 9 bits válidos
	temp = temp_raw * 0.5; // Convertir a grados Celsius
	return temp;
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