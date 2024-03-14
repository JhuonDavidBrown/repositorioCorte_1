/*
 * GccApplication2.c
 *
 * Created: 3/14/2024 10:15:53 AM
 * Author : USUARIO
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define D1    PD6
#define D2    PD2
#define BTNA  PC5
#define BTNB  PC4

#define getBTNA()  (PINC & (1<<BTNA))
#define getBTNB()  (PINC & (1<<BTNB))

enum{
	MODO1=1,
	MODO2
};

char contadorA=1, contadorB=0;
char modo=MODO1;

int main(void)
{
	// Configuramos el puerto PD como salidas para D1 y D2;
	DDRD |= (1<<D1) | (1<<D2);
	
	// Configuramos el puerto PC como entradas para BTNA y BTNB;
	DDRC &= ~((1<<BTNA) | (1<<BTNB));
	
	while (1)
	{
		
		if(modo==MODO1){
			if(contadorA==40){
				PORTD ^= (1<<D1);
				contadorA=0;
			}
			if(contadorB==70){
				PORTD ^= (1<<D2);
				contadorB=0;
			}
		}
		if(modo==MODO2){
			if(contadorA==90){
				PORTD ^= (1<<D1);
				contadorA=0;
			}
			if(contadorB==20){
				PORTD ^= (1<<D2);
				contadorB=0;
			}
		}
		
		
		
		if(getBTNA() == 0 && getBTNB() != 1){
			while(getBTNA() == 0 && getBTNB() != 1);
			if(modo==MODO1){
				modo=MODO2;
			}
			else if(modo==MODO2){
				modo=MODO1;
			}
		}
		if(getBTNA() != 0 && getBTNB() == 0){
			while(getBTNA() != 0 && getBTNB() == 0);
			if(modo==MODO1){
				modo=MODO2;
			}
			else if(modo==MODO2){
				modo=MODO1;
			}
		}
		
		contadorA++;
		contadorB++;
		
		
		_delay_ms(10);
	}
}
