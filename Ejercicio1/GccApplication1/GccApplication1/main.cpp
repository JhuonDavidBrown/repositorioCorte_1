/*
 * GccApplication1.cpp
 *
 * Created: 3/13/2024 7:59:04 PM
 * Author : USUARIO
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL

#define LED1 PD6
#define LED2 PD2
#define PULSADOR PC4

int main(void) {
	// Configura LED1 y LED2 como salidas
	DDRD |= (1 << LED1) | (1 << LED2);
	
	// Apaga LED1 y LED2 inicialmente
	PORTD &= ~(1 << LED1);
	PORTD &= ~(1 << LED2);
	
	// Configura PULSADOR como entrada y habilita la resistencia de pull-up interna
	DDRC &= ~(1 << PULSADOR);
	PORTC |= (1 << PULSADOR);

	while (1) {
		// Parpadeo de LED1
		PORTD |= (1 << LED1); // Enciende LED1
		_delay_ms(140);
		PORTD &= ~(1 << LED1); // Apaga LED1
		_delay_ms(140);

		// Verifica el estado del botón
		if (PINC & (1 << PULSADOR)) { // Si el botón no está presionado
			PORTD &= ~(1 << LED2); // Apaga LED2
			} else { // Si el botón está presionado
			PORTD ^= (1 << LED2); // Conmuta el estado de LED2
			_delay_ms(200); // Retardo para debounce
		}
	}

	return 0;
}

