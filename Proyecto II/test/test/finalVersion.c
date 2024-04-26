#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16E6UL  // Fclk = 16 MHz.

#define Op 0

void ConfigINT0(void);

uint8_t Modo = 0;
uint16_t ContD1 = 0, ContD2D3;

int main(void)
{
	DDRC |= 0b00000111;		//Configura: PC2-PC0 = Out
	PORTC |= 0b00000111;	//LED3-LED1 (PC2-PC0) = 1 (encendidos)
	
	DDRD &= 0b11111011;		//Configura: PD2/INT0 = In
	PORTD |= 0b00000100;	//Configura: PD2 con pull up
	
	ConfigINT0();
	
	while (1)
	{
		if (++ContD1 == 400)  //2s/5ms = 400
		{
			PORTC ^= 0b00000001;  //~LED1
			ContD1 = 0;
		}

		ContD2D3++;
		
		if (Modo == 1 && ContD2D3 == 300)  //1.5s/5ms = 300
		{
			PORTC ^= 0b00000010;  //~LED2
			ContD2D3 = 0;
		}
		
		if (Modo == 2 && ContD2D3 == 300)  //1.5s/5ms = 300
		{
			PORTC ^= 0b00000100;  //~LED3
			ContD2D3 = 0;
		}
		
		_delay_ms(5);
	}
}

void ConfigINT0(void){
	EICRA = (EICRA & 0b11111100)|0b00000010;	//Flanco caída
	
	EIFR &= 0b11111110;		//INTF0 = 0 (flag de IRQ)
	EIMSK |= 0b00000001;	//INT0 = 1 (Habilitacion particular)
	sei();	//I=1 (Habilitacion global)
}

ISR(INT0_vect){
	if ((PIND & 0b00000100) == Op) //Pul(PD2/INT0) = Op?
	{
		PORTC = 0b00000111;	//LED3-LED2-LED1 = ON
		ContD2D3 = 0;
		if (++Modo == 4) Modo = 0;
	}
}