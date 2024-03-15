/*
 * GccApplication2.c
 *
 * Created: 3/14/2024 10:15:53 AM
 * Author : USUARIO
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define D1    PIND6
#define D2    PIND2
#define PUL1  PINC4
#define PUL2  PINC5
#define getPUL1()  ( PINC&(1<<PUL1) )
#define getPUL2()  ( PINC&(1<<PUL2) )


/* #define D1    PINB5
#define D2    PINB1
#define BTNA  PINB6
#define BTNB  PINB7
#define getBTNA()  ( PINB&(1<<BTNA) )
#define getBTNB()  ( PINB&(1<<BTNB) )*/


enum{
	MODO1=1,
	MODO2	
};

char contadorPul1=1, contadorPul2=0;
char modo=MODO1;



int main(void)
{
	//Configuramos el puerto PD como salidas para D1 y D2;
    DDRD |=  ( (1<<D1)   | (1<<D2) );
	
	//Configuramos el puerto PC como entradas para BTNA y BTNB;
	DDRC &= ~( (1<<PUL1) | (1<<PUL2) );
	
    while (1) 
    {
		if(modo==MODO1){
			if(contadorPul1==40){
				PORTB ^= (1<<D1);
				contadorPul1=0;
			}
			if(contadorPul2==70){
				PORTB ^= (1<<D2);
				contadorPul2=0;
			}
		}
		if(modo==MODO2){
			if(contadorPul1==90){
				PORTB ^= (1<<D1);
				contadorPul1=0;
			}
			if(contadorPul2==20){
				PORTB ^= (1<<D2);
				contadorPul2=0;
			}
		}
		
		
		
		if( getPUL1() == 0 && getPUL2() !=1 ){
			while(getPUL1() == 0 && getPUL2() !=1);
			if(modo==MODO1){
				modo=MODO2;
			}
			if(modo==MODO2){
				modo=MODO1;
			}
		}
		if( getPUL1() != 0 && getPUL2() == 0){
			while(getPUL1() != 0 && getPUL2() == 0);
			if(modo==MODO1){
				modo=MODO2;
			}
			if(modo==MODO2){
				modo=MODO1;
			}
		}
		
		contadorPul1++;
		contadorPul2++;
		
		
		_delay_ms(10);
    }
}
