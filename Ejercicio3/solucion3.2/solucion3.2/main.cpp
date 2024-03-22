/*
 * solucion3.2.cpp
 *
 * Created: 22/03/2024 10:40:11 a. m.
 * Author : vsvrr
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define getStatusC4() (PINC & (1<<PINC4))
uint16_t Display_7seg[16]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
uint8_t contador = 0;
int main(void)
{
	DDRD = 0b11111110;  //D como salida
	DDRC &= ~(1<<PINC4); //C4 como entrada
	while (1) 
    {
		if(getStatusC4() !=0)
		{
			while(getStatusC4()!=0);//esperar hasta que no este op
			contador ++;
			if(contador>9)contador=0;
		}
		PORTD = Display_7seg[contador];
		_delay_ms(200); //
    }
}

