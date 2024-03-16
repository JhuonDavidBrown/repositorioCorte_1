/*
 * solucion2_2.cpp
 *
 * Created: 16/03/2024 3:17:58 p. m.
 * Author : vsvrr
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define op 0
#define led1 PD6 
#define led2 PD2
#define pul1 PC4
#define pul2 PC5

uint8_t contadorD1= 0;
uint8_t contadorD2 = 0;


void modo1(void);
void modo2(void);

int main(void)
{
	DDRD |= (1<<led1)|(1<<led2);
	PORTD &= ~((1 << led1) | (1 << led2)); // Apagar los LEDs al inicio
	DDRC = 0b11001111;
    while (1) 
    {
		if((PINC &(1<<pul1))== op)
		{
			while( (PINC& (1<<pul1))==op){
		
				modo1();
				_delay_ms(5);
				contadorD1++;
				contadorD2++;
			}
			 // PORTD^= (1<<led1)|(1<<led2); conmuta cada vez que se pulsa
		}
		if ( (PINC & (1<<pul2)) ==op)
		{
			while( (PINC&(1<<pul2))==op)
			{
				modo2();
				_delay_ms(5);
				contadorD1++;
				contadorD2++;
			}
			// PORTD^= (1<<led1)|(1<<led2);	 conmuta cada vez que se pulsa
		}
    }
}
void modo1(void)
{
	if(contadorD1==80){ //0.4s
		PORTD ^= (1<<led1);
		contadorD1==0;
	}
	if(contadorD2==140){ //0.7s
		PORTD ^=(1<<led2);
		contadorD2=0;
	}
}
void modo2(void)
{
	if(contadorD1==180){ //0.9s
		PORTD^=(1<<led1);
		contadorD1==0;
	}
	if (contadorD2==40){ //0.2s
		PORTD^=(1<<led2);
		contadorD2=0;
	}
}