/*
 * Universidad del Valle de Guatemala
 * Electrónica Digital 2
 * Archivo: Proyecto_1_Digital_2
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

#define LM75_ADDR 0x48  // Dirección del LM75 con A0, A1, A2 en GND

uint8_t direccion;
uint8_t temp;       // Variable temporal 
uint8_t bufferI2C;  // Variable donde se escribe los códigos de la comunicación I2C.
uint8_t valorI2C_humedad = 0;  // Variable para guardar cada lectura de I2C de los slaves. 
uint8_t valorI2C_distancia = 0;  // Variable para guardar cada lectura de I2C de los slaves. 

char bufferRX[10];  // Buffer para almacenar los datos recibidos por UART
uint8_t indiceRX = 0;  // Índice para el buffer

void initPorts(void);
void refreshPORT(uint8_t valor);
float LM75_ReadTemperature();
void initUART9600(void);
void writeUART(char caracter);
void writeTextUART(char* texto);
void procesarComando(char *comando);
void Humedad();
void Distancia ();

int main(void)
{
	I2C_Master_Init(100000,1); // inicializar como Master Fscl 100kHz, prescaler 1
	initLCD8bits();
	initPorts();
	initUART9600();
	
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
    //**************** Comunicación con sensor de temperatura LM75 *********************
    PORTB |= (1 << PORTB5);  // Encender LED indicador de comunicación I2C

    float temperatura = LM75_ReadTemperature();
	Humedad();
	Distancia ();
    
    // Mostrar en LCD
    LCD_Set_Cursor(11, 2);
    LCD_Write_Char(CERO + ((int)temperatura / 10));
    LCD_Write_Char(CERO + ((int)temperatura % 10));
    LCD_Write_Char('.');
    LCD_Write_Char(CERO + ((int)(temperatura * 10) % 10));
    LCD_Write_Char('C');

    // Enviar datos de temperatura por UART en el formato esperado por el ESP32
    writeUART('T');  // Etiqueta de temperatura
    writeUART(':');
    writeUART(CERO + ((int)temperatura / 10));
    writeUART(CERO + ((int)temperatura % 10));
    writeUART('.');
    writeUART(CERO + ((int)(temperatura * 10) % 10));
    writeUART(' ');  // Espacio para separar los valores

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

    // Control de LED según temperatura
    if (temperatura > 30.0) {
        PORTC &= ~(1 << PORTC0);  // Encender LED si la temperatura es mayor a 30°C
    } else {
        PORTC |= (1 << PORTC0);   // Apagar LED si la temperatura es menor o igual a 30°C
		I2C_Master_Start();
		I2C_Master_Write((slave2 << 1) | 0); // Dirección del esclavo (0x40) en modo escritura
		I2C_Master_Write((uint8_t)temperatura); // Enviar temperatura como entero
		I2C_Master_Stop();

    }

    
    _delay_ms(50);
}

}

void Distancia (void){
	//**************** Comunicación con sensor ultrasónico (slave2) *********************
    I2C_Master_Start();
    bufferI2C = slave2 << 1 & 0b11111110;
    
    temp = I2C_Master_Write(bufferI2C);
    if (temp != 1) {
        I2C_Master_Stop();
    }
    I2C_Master_Write('R');
    I2C_Master_Stop();
    _delay_ms(500);

    I2C_Master_Start();
    bufferI2C = slave2 << 1 | 0b00000001;
    
    temp = I2C_Master_Write(bufferI2C);
    if (temp != 1) {
        I2C_Master_Stop();
    }

    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    
    valorI2C_distancia = TWDR;
    I2C_Master_Stop();

    LCD_Set_Cursor(1, 2);
    Convert_Value(valorI2C_distancia);

}

void Humedad (void){
	//**************** Comunicación con sensor de humedad (slave1) *********************
    I2C_Master_Start();
    bufferI2C = slave1 << 1 & 0b11111110;
    
    temp = I2C_Master_Write(bufferI2C);
    if (temp != 1) {
        I2C_Master_Stop();
    }
    I2C_Master_Write('R');
    I2C_Master_Stop();
    _delay_ms(500);

    I2C_Master_Start();
    bufferI2C = slave1 << 1 | 0b00000001;
    
    temp = I2C_Master_Write(bufferI2C);
    if (temp != 1) {
        I2C_Master_Stop();
    }

    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    
    valorI2C_humedad = TWDR;
    I2C_Master_Stop();

    // Mostrar en LCD
    LCD_Set_Cursor(7, 2);
    Convert_Value(valorI2C_humedad);
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

void writeTextUART(char* texto) {
	uint8_t i;
	for (i = 0; texto[i]!= '\0'; i++){
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = texto[i];
	}
}

ISR(USART_RX_vect) {
	char recibido = UDR0;  // Leer el dato recibido
	
	if (recibido == '\n') {  // Si el dato recibido es un salto de línea
		bufferRX[indiceRX] = '\0';  // Terminar el string
		//procesarComando(bufferRX);  // Procesar el comando
		indiceRX = 0;  // Reiniciar el índice
		} else {
		bufferRX[indiceRX++] = recibido;  // Guardar el dato en el buffer
	}
}


void procesarComando(char *comando) {
	if (strcmp(comando, "riegoon") == 0) {
		// Selecciona el esclavo de dirección 0x30 (controlador de riego)
		I2C_Master_Start();
		I2C_Master_Write((slave1 << 1) & 0b11111110);  // Dirección del esclavo para escritura
		I2C_Master_Write('1');  // Envía el comando de activar riego (puedes cambiar el dato a lo que se necesite)
		I2C_Master_Stop();
		
		} else if (strcmp(comando, "ventilaron") == 0) {
		// Selecciona el esclavo de dirección 0x40 (controlador de ventilación)
		I2C_Master_Start();
		I2C_Master_Write((slave2 << 1) & 0b11111110);  // Dirección del esclavo para escritura
		I2C_Master_Write('1');  // Envía el comando de activar ventilación (puedes cambiar el dato a lo que se necesite)
		I2C_Master_Stop();
		
		}
}