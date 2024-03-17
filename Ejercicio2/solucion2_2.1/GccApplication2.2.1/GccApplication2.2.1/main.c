/*
 * GccApplication2.2.1.c
 *
 * Created: 3/17/2024 9:18:48 AM
 * Author : USUARIO
 */ 

#include <avr/io.h>


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define D1    PIND6
#define D2    PIND5
#define BTNA  PINC5 // pulsador 2
#define BTNB  PINC4 // pulsador 1

#define getBTNA()  ( PINC&(1<<BTNA) )
#define getBTNB()  ( PINC&(1<<BTNB) )

enum{
	MODO1=1,
	MODO2
};

char contadorA=1, contadorB=0;
char modo=MODO1;



int main(void)
{
	//Configuramos el puerto PD como salidas para D1 y D2;
	DDRD |=  ( (1<<D1)   | (1<<D2)   );
	
	//Configuramos el puerto PC como entradas para BTNA y BTNB;
	DDRC &= ~( (1<<BTNA) | (1<<BTNB) );
	
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
		
		
		
		if( getBTNA() == 0 && getBTNB() !=1 ){
			while(getBTNA() == 0 && getBTNB() !=1);
			if(modo==MODO1){
				modo=MODO2;
			}
			if(modo==MODO2){
				modo=MODO1;
			}
		}
		if( getBTNA() != 0 && getBTNB() == 0){
			while(getBTNA() != 0 && getBTNB() == 0);
			if(modo==MODO1){
				modo=MODO2;
			}
			if(modo==MODO2){
				modo=MODO1;
			}
		}
		
		contadorA++;
		contadorB++;
		
		
		_delay_ms(10);
	}
}

