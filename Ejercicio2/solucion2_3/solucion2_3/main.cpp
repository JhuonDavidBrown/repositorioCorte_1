/*
 * solucion2_3.cpp
 *
 * Created: 18/03/2024 9:42:53 a. m.
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

uint8_t bPul = 0;
uint8_t bModo = 0;
void modo1(void);
void modo2(void);
void pulsadores();

int main(void)
{	
	DDRD |= (1<<led1)|(1<<led2); //Definiendo puertos de los leds como salida
	PORTD &= ~((1<<led1)|(1<<led2)); //  apagar los LEDs inicialmente
	DDRC = 0b11001111;
	
	while (1)
	{
		pulsadores();
		if(bModo=1){
			modo1();
		}
		else{
			modo2();
		}
		_delay_ms(5);
		
	}
		
}

void pulsadores(){
	if( (pul1==op && pul2!=op)||(pul1!=op && pul2==op) ){
		if(bPul==1){
			bModo=~bModo;
			bPul=0;
		}
		bPul=1;
	}
}
void modo1(void)
{
	contadorD1++;
	contadorD2++;
	if(contadorD1==80){ //0.4s
		PORTD =~(1<<led1);
		contadorD1=0;
	}
	if(contadorD2==140){ //0.7s
		PORTD =~(1<<led2);
		contadorD2=0;
	}
}
void modo2(void)
{
	contadorD1++;
	contadorD2++;
	if(contadorD1==180){ //0.9s
		PORTD=~(1<<led1);
		contadorD1=0;
	}
	if (contadorD2==40){ //0.2s
		PORTD=~(1<<led2);
		contadorD2=0;
	}
}