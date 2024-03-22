/*
 * solucion3.5
 *
 * Created: 17/03/2024 12:10:45p. m.
 * Author : juan
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_STATE() (PIND&(1<<PIND0))


unsigned char numero_anodo [10] = {
	0xC0,
	0xF9,
	0xA4,
	0xB0,
	0x99,
	0x92,
	0x83,
	0xF8,
	0x80,
	0x98,
};

unsigned char numero_catodo [10] ={
		0x3F,
		0x06,
		0x5B,
		0x4F,
		0x66,
		0x6D,
		0x7C,
		0x07,
		0x7F,
		0x67,	
	
};

uint8_t contador = 0;

int main(void)
{
	DDRD = 0xFF;
	PORTB = 0xFF;

	DDRD = 0xFF;
	PORTB = 0x00;
	
	
    while (1) 
    {

contador++;
if(contador > 9) contador = 0;


PORTB = numero_anodo [contador];
PORTD = numero_catodo [contador];



_delay_ms(500);
}

}