/*solucion3.1.cpp
 * Solution coding ejercicio 3
 * Author : Juan David, Juan Manuel, Andres Gomez */ 
#include <avr/io.h>
#define F_CPU 16000000 //Frecuencia 8mhz
#include <util/delay.h> //libreria pa usar delays
#include <stdint.h>  //Libreria pa variables enteras
#define BUTTON_STATE() (PINC&(1<<PINC4)) //asignar el nombre button al estado del pin P0

// uint8_t Display_7seg[10]= {191,134,219,207,230,237,253,135,255,231}; //Arreglo de numeros del 0 a 9
uint16_t Display_7seg[16]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // hexadecimal 0 a f
uint8_t Contador=0; //variable que contara el numero y mostrara en el e display

void Register_setting(void);  //definir funcion

int main()
{
	Register_setting();              //llamdo a la funcion de registros para configurar puertos
	
	while(1)						//bucle main infinito
	{
		if(BUTTON_STATE()!=1)          //condicion de pulsador fue presionado
		{
			while(BUTTON_STATE()!=1);  //esperar mientras el pulsador no este presionado
			Contador++;          //incrementar valor
			if (Contador>15)    // condicion
			{
				Contador=0;    // reinicia contador si pasa de 16
			}
		}
		PORTD=Display_7seg[Contador];   //mostrar el valor del elemento del arrglo                                  
		_delay_ms(1000);    //delay de 20ms
	}	
}
void Register_setting(void) // funcion de registros
{
	DDRD |= 0xFE; //configurar pines D1 a D7 como salida
	//DDRD=0b11111110;  //configurar puerto D como salida
	PORTD = 0xff;
	DDRC&=~(1<<PINC4); //Configurar pin B0 como entrada
	
}

