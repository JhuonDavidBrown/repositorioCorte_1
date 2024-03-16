/*
 * GccApplication1.cpp
 *
 * Created: 3/13/2024 7:59:04 PM
 * Author : USUARIO
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>



#define LED1     PD6
#define LED2     PD2
#define PULSADOR PC4


char contador=0;


void logicaLed1(void){
	// Parpadeo de LED1
	if(contador==14){ //140 ms
		PORTD ^= (1 << LED1); // Enciende LED1
		contador=0;
	}
}

int main(void) {
	
	DDRD |= (1 << LED1) | (1 << LED2);
	DDRC &= ~(1 << PULSADOR); // Make pin 5 of port C as a input
	
	// Apaga LED1 y LED2 inicialmente;
	PORTD &= ~(1 << LED1);
	
	while (1) {
		if ( (PINC & (1 << PULSADOR)) == 0){
			while( (PINC & (1 << PULSADOR)) == 0  ){
				logicaLed1();
				_delay_ms(10);
				contador++;
			}
			PORTD ^= (1 << LED2); //PIN4 of port D is high
		}
		
		logicaLed1();
		_delay_ms(10);
		contador++;
		
	}

	return 0;
}