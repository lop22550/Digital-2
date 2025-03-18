/*
 * ADC.c
 *
 * Created: 13/02/2025 11:56:15
 *  Author: bjosu
 */ 

 #include <avr/io.h>


void initADC (void){
	//Configuración del ADC
	ADMUX = 0b0101; //Selectiona el puerto ADC5
	ADCSRA = 0;
	ADMUX |= (1<<ADLAR); //AJUSTE A LA IZQUIERDA (SOLO SE USA ADCH)
	ADMUX |= (1<<REFS0); //Selecciona un voltaje interno de referencia de 5V.
	ADMUX &= ~(1<<REFS1);
	
	//SE ENCIENDE ADC
	ADCSRA |= (1<<ADEN);
	
	// SE HABILITA LA INTERRUPCIÓN DEL ADC
	ADCSRA |= (1<<ADIE);
	
	//PRESCALER DE 128 (125kHZ)
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	//Deshabilita la entrada digital PC5
	DIDR0 |= (1<<ADC5D);
}