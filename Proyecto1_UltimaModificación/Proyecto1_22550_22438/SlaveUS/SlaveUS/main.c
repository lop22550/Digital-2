//*****************************************************************************
// Universidad del Valle de Guatemala
// Electrónica Digital 2
// Archivo: Slave_2_Proyecto_invernadero
// Hardware: ATMega328p
// Autor: Adriana Marcela Gonzalez, Boris Josué López
// Carnet: 22438, 22550
//*****************************************************************************
// Librerías
//*****************************************************************************

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C/I2C.h"

#define SlaveAddress 0x40


uint8_t buffer = 0;
uint8_t lecturaUS = 0;  //Almacena el valor de la lectura del sensor ultrásónico
uint8_t valorUS = 0;    //Almacena la lectura ya operada para mostar la distancia en un display.

volatile uint16_t pulse = 0;   //Almacena el pulso enviado por el sensor
volatile uint8_t distance = 0xFF; //Se convierte la señal de pulso a un valor para mostrar en cm
/* valorUS = lecturaUS/58; for centimeter
   valorUS = lecturaUS/148; for inches
*/  
volatile uint8_t temperatura = 0;
 

//-------- Prototipos de función ------------------------------ 
void initUS(void);           //Se inicializa los pines, el Timer1 y la interrupción de Pin Change.
void US_Request (void);      // Inicia la comunicación con el sensor ultrasónico
uint8_t US_Receive (void);   //Esta función ya no se utiliza.



int main(void)
{
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	
	I2C_Slave_Init(SlaveAddress);
	initUS();
	
	sei(); //Habilita las interrupciones
	
	// Configurar A0 como salida (para el motor DC)
	DDRC |= (1 << DDC3);
	PORTC &= ~(1 << PORTC3);  // Motor apagado por defecto
	
    while(1)
    {
		//Se inicia calibración del sensor
		US_Request();
		//Delay para calibración.
		_delay_ms(100);
		
		// Control del motor según la temperatura recibida
		if (temperatura <= 30) {
			PORTC |= (1 << PORTC3);  // Encender motor
			} else {
			PORTC &= ~(1 << PORTC3); // Apagar motor
		}
		
		if(buffer == 'R'){
			//Se enciende LED indicador de comunicación. 
			PINB |= (1<<PINB5);
			buffer = 0;}
		
    }
}



//-------- Funciones ------------------------------ 
void initUS(void){
	DDRC |= (1 << DDC0);  // Configurar PC0 como salida; Trigger pin
	PORTC &= ~(1 << PORTC0); //Asegurar señal en bajo antes de iniciar comunicación
	//DDRC &= ~(1<<PINC1); // Configurar PC1 como entrada; Echo pin 
	PORTC |= (1 << PINC1); // Pull-up en ECHO_PIN

	
	// Configuración Pin Change para PC1 (Echo del US)
	PCICR |= (1 << PCIE1);   // Habilita PCINT1 (PORTC)
	PCMSK1 |= (1 << PCINT9); // Habilita PCINT9 (PC1)
	
	TCCR1B |= (1 << CS11); // Prescaler 8
	TCNT1 = 0; // Inicia en 0
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	ICR1 = 20000; // 20 ms (50 Hz)

}

void US_Request(void){
	PORTC |= (1 << PINC0);  // Enviar señal alta
	_delay_us(10);  // Mantener señal baja al menos 10us
	PORTC &= ~(1 << PINC0);  // Bajar la señal
	
	
}

uint8_t US_Receive(void){
	US_Request();
	
	uint8_t data = 0; 
	
	//Esperar a que ECHO se ponga en alto
	while (!(PINC & (1 << PINC1)));
	
	// Contar el tiempo que ECHO permanece en alto
	uint16_t count = 0;
	while (PINC & (1 << PINC1)) {
		_delay_us(10);
		count++;
		if (count >= 4000) return 400; // Si se pasa el tiempo, devolver distancia máxima (~2m)
	}

	return count;
}


//---Interrupciones------------------------------------------------------------------------------------------
ISR(TWI_vect)
{
	uint8_t estado;
	estado = TWSR & 0xFC;
	switch (estado) {
		case 0x60:
		case 0x70:
		TWCR |= (1 << TWINT);
		break;
		case 0x80:
		case 0x90:
		temperatura = TWDR;  // Guardar temperatura recibida
		TWCR |= (1 << TWINT) | (1 << TWEA);
		break;
		case 0xA8:
		case 0xB8:
		TWDR = distance; // Cargar el dato
		TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA); // Inicia el envío
		break;
		default: // Se libera el bus de cualquier error
		TWCR |= (1 << TWINT) | (1 << TWSTO);
		break;
	}
}

ISR(PCINT1_vect) {
	static uint8_t last_state = 0;
	uint8_t current_state = (PINC & (1 << PINC1)) ? 1 : 0;
	
	if (current_state != last_state) {
		if (current_state == 1) { // Flanco ascendente (inicio del pulso)
			TCNT1 = 0; // Reinicia el timer
			} else { // Flanco descendente (fin del pulso)
			pulse = TCNT1; // Captura el ancho del pulso
			// Cálculo correcto: (pulse_width * 0.5 µs) / 58 µs/cm
			distance = (pulse * 0.5) / 58;
			if (distance > 200 || pulse == 0) {
				distance = 0xFF; // Distancia fuera de rango o error
			}
		}
		last_state = current_state;
	}
}