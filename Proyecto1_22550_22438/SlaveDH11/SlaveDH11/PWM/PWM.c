#include "PWM.h"  // Incluye el archivo de encabezado que declara las funciones y constantes

// Función para inicializar el PWM en el canal A del Timer 0
void initPWM0FastA(uint8_t inverted, uint16_t precaler){
	DDRD |= (1<<DDD6);  // Establece el pin de salida para el canal A del Timer 0
	PORTD &= ~(1<<PORTD6);
	
	TCCR0A = 0;  // Borra los bits de control del Timer 0
	if (inverted == invertido) {
		TCCR0A |= (1<<COM0A1)|(1<<COM0A0);  // Configura la salida del canal A en modo PWM invertido
		} else {
		TCCR0A |= (1<<COM0A1);  // Configura la salida del canal A en modo PWM no invertido
	}
	
	TCCR0A |= (1<<WGM01)|(1<<WGM00);  // Configura el Timer 0 en modo PWM rápido (modo 7)
	
	if (precaler == 1024) {
		TCCR0B |= (1<<CS02)|(1<<CS00);  // Configura el preescalador del Timer 0 en 1024
	}
}

// Función para inicializar el PWM en el canal B del Timer 0
void initPWM0FastB(uint8_t inverted, uint16_t precaler){
	DDRD |= (1<<DDD5);  // Establece el pin de salida para el canal B del Timer 0
	
	if (inverted) {
		TCCR0A |= (1<<COM0B1)|(1<<COM0B0);  // Configura la salida del canal B en modo PWM invertido
		} else {
		TCCR0A |= (1<<COM0B1);  // Configura la salida del canal B en modo PWM no invertido
	}
	
	TCCR0A |= (1<<WGM01)|(1<<WGM00);  // Configura el Timer 0 en modo PWM rápido (modo 7)
	
	TCCR0B |= (1<<CS02)|(1<<CS00);  // Configura el preescalador del Timer 0 en 1024
}

// Función para actualizar el valor del registro de comparación del canal A del Timer 0
void updateDCA(uint8_t duty){
	OCR0A = ((duty*256)/100)-1;  // Actualiza el valor del registro de comparación para el canal A del Timer 0
}

// Función para actualizar el valor del registro de comparación del canal B del Timer 0
void updateDCB(uint8_t duty){
	OCR0B = duty;  // Actualiza el valor del registro de comparación para el canal B del Timer 0
}


void initServoPWM() {
	// Configurar PB1 (OC1A) como salida
	DDRB |= (1 << PB1);

	// Modo Fast PWM con TOP en ICR1 (modo 14)
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Preescalador de 8

	// Frecuencia de 50 Hz (Periodo = 20 ms)
	ICR1 = 39999;

	// Inicializar en posición neutra (90° ? 1.5 ms)
	OCR1A = 2999;
}

// Configura el ángulo del servo (0° - 180°)
void setServoAngle(uint8_t angle) {
	if (angle > 180) {angle = 180;}
	OCR1A = ((angle * 2000) / 180) + 999; // Mapear 0° (1ms) a 180° (2ms)
}

void initPWM1A (){
	DDRB |= (1<<DDB1);	//Se está configurando el puerto OC1A como salida
	
	TCCR1A = 0;
	TCCR1B = 0;
	
	TCCR1A |= (1<<COM1A1); // Configurando OC1A como No invertido
	TCCR1A |= (1<<WGM11); //Configurando Modo Fast PWM con ICR1 como TOP
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS12)|(1<<CS10); //Configurando Modo Fast PWM con ICR1 como TOP | Prescaler de 1024
	
	ICR1H = (PWM_TOP & 0xFF00)>>8;
	ICR1L = (PWM_TOP & 0x00FF);

	OCR1AH =(MIN1 & 0xFF00)>>8;
	OCR1AL = (MIN1 & 0x00FF);
}

void updateDutyCycleA1(uint8_t angulo){
	//uint8_t Mappeo = (valor_ADC / 255)*(MAX-MIN)+MIN;
	uint8_t Mappeo1 = (angulo / 6);
	uint8_t Senal_Servo1 = Mappeo1;

	OCR1AH = (Senal_Servo1 & 0xFF00)>>8;
	OCR1AL = (Senal_Servo1 & 0x00FF);
}