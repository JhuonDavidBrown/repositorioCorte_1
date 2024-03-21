/*
 * GccApplication1.cpp
 *
 * Created: 3/13/2024 7:59:04 PM
 * Author : Andres gomez
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>



#define LED1     PD6
#define LED2     PD2
#define PULSADOR PC4


char contador=0;


void logicaLed1(void){
	
	if(contador==14){ 
		PORTD ^= (1 << LED1); 
		contador=0;
	}
}

int main(void) {
	
	DDRD |= (1 << LED1) | (1 << LED2);
	DDRC &= ~(1 << PULSADOR); 
	
	
	PORTD &= ~(1 << LED1);
	
	while (1) {
		if ( (PINC & (1 << PULSADOR)) == 0){
			while( (PINC & (1 << PULSADOR)) == 0  ){
				logicaLed1();
				_delay_ms(10);
				contador++;
			}
			PORTD ^= (1 << LED2); 
		}
		
		logicaLed1();
		_delay_ms(10);
		contador++;
		
	}

	return 0;
}