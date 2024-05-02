/*
 * contadorDisplay4.cpp
 *
 * Created: 26/04/2024 2:46:01 p. m.
 * Author : vsvrr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16E6UL // Fclk = 16 MHz.
#define  Op 0

uint8_t flag = 0;

uint8_t unidades = 1;
uint8_t decenas = 2;
uint8_t centenas = 3;
uint8_t miles= 4;
uint8_t Modo = 0;
uint16_t ContD1 = 0, ContD2D3;
void ConfigINT0(void);
void ConfigINT1(void);
void Display(void);
void Reloj(void);
void ConfigTMR0(void);


uint8_t stop = 0;
uint8_t togg = 0;

int main(void)
{
	
	DDRB |= 0b00001111; //bit pb0-pb3 como salida
	
	DDRC |= 0b00000111; //bit pc0-pc2 como salida (3leds)
	PORTC |= 0b00000111;//los 3 leds encendidos
	
	DDRD &= 0b11110011;//pd3(int1)y pd2(int0)definido como entrada
	PORTD |= 0b00001100;//pull up activado
	
	DDRD |= 0b11110000;//pd4-pd7 como salida
	PORTD |= 0b11110000;//pull up activado
	
	DDRC |= 0b00000111;		//Configura: PC2-PC0 = Out
	PORTC |= 0b00000111;	//LED3-LED1 (PC2-PC0) = 1 (encendidos)
	
	ConfigINT1();
	ConfigINT0();
	ConfigTMR0();
	
    while (1) 
    {
		if (++ContD1 == 400)  //2s/5ms = 400
		{
			PORTC ^= 0b00000001;  //Conmutar LED1
			ContD1 = 0;
		}
		ContD2D3++;

		if (Modo == 1 && ContD2D3 == 300)  //1.5s/5ms = 300
		{
			PORTC ^= 0b00000010;  //Conmutar LED2
			ContD2D3 = 0;
		}
		if (Modo == 2 && ContD2D3 == 300)  //1.5s/5ms = 300
		{
			PORTC ^= 0b00000100;  //Conmutar LED3
			ContD2D3 = 0;
		}
		Display();
		_delay_ms(5);
		//asm("NOP");
		
		
    }
}
void Display(void){
	static uint8_t Cont = 0;
	if(!stop)
	{
		if (++Cont == 1)
		{
			PORTD |= 0b10000000;//PD7 = 1: Inactiva DispM
			PORTB = (PORTB & 0xF0) |unidades; //Refresca Unidades
			PORTD &= 0b11101111; //PD4 = 0: Activa DispU
		}
		if (Cont == 2)
		{
			PORTD |= 0b00010000;//PD4 = 1: Inactiva DispU
			PORTB = (PORTB & 0xF0) |decenas; //Refresca Decenas
			PORTD &= 0b11011111; //PD5 = 0: Activa DispD
		}
		if (Cont == 3)
		{
			PORTD |= 0b00100000;//PD5 = 1: Inactiva DispD
			PORTB = (PORTB & 0XF0) |centenas; //Refresca Centenas
			PORTD &= 0b10111111; //PD6 = 0: Activa Dispc
		}
		if (Cont == 4)
		{
			PORTD |= 0b01000000; //PD6 = 1: Inactiva DispC
			PORTB = (PORTB & 0xF0) |miles; //Refresca DispM
			PORTD &= 0b01111111; //PD7 = 1: Activa DispM
			Cont = 0;
		}
	}
	
}
void Reloj(void){
	if (++unidades == 10)
	{
		unidades = 0;
		if (++decenas == 6)
		{
			decenas = 0;
			if (++centenas == 10)
			{
				centenas = 0;
				if (++miles == 10)
				{
					miles = 0;
				}
			}	
		}	
	}	
}

ISR(TIMER0_OVF_vect){
	static uint8_t Cont = 0;
	TCNT0 = 131; //valor inicial TMR0
	if(++Cont == 250) // 1/4ms =250
	{
		Reloj();
		PORTC ^= 0b00000100; //D3(PC2) conmuta cada segundo	
	}
}
ISR(INT0_vect){
	
	if ((PIND & (1 << PD2)) == Op) {
		togg = !togg; // Cambiar el estado de togg
		if (togg) {
			stop = 1; // Detener el contador del display
			} else {
			stop = 0; // Reanudar el contador del display
		}
	}
	
	/*
	if(flag == 0)
	{
		if ((PIND & 0b00000100) == Op)
		{
			++flag;
			Display();
			
		}
	}
	if(flag==1 && (PIND & 0b00000100) == Op)
	{
		
		
		
	}
	*/
}
ISR(INT1_vect){
	if ((PIND & 0b00001000) == Op)
	{
		PORTC = 0b00000111;
		ContD2D3 = 0;
		if (++Modo == 4) Modo = 0;
	}
}
void ConfigINT0(void){
	#warning "Borre comentario de la OPCION requerida."
	//EICRA &= 0b11111100; //Nivel bajo
	//EICRA = (EICRA & 0b11111100)|0b00000001; //Todo flanco
	EICRA = (EICRA & 0b11111100)|0b00000010; //Flanco caída
	//EICRA = (EICRA & 0b11111100)|0b00000011; //flanco subida
	EIFR &= 0b11111110; //INTF0 = 0 (flag de IRQ)
	EIMSK |= 0b00000001; //INT0 = 1 (Habilitación particular)
	sei(); //I=1 (Habilitación global)
}
void ConfigINT1(void){
	#warning "Borre comentario de la OPCION requerida."
	//EICRA &= 0b11111100; //Nivel bajo
	//EICRA = (EICRA & 0b11111100)|0b00000001; //Todo flanco
	EICRA = (EICRA & 0b11111100)|0b00000010; //Flanco caída
	//EICRA = (EICRA & 0b11111100)|0b00000011; //flanco subida
	EIFR &= 0b11111110; //INTF0 = 0 (flag de IRQ)
	EIMSK |= 0b00000010; //INT1 = 1 (Habilitación particular)
	sei(); //I=1 (Habilitación global)
}void ConfigTMR0(void){
	#warning "Borre comentario de la OPCION requerida."
	//TCCR0B =0x00; //Modo STOP
	//TCCR0B =0b0000 0001; //FM = 1
	//TCCR0B =0b0000 0010; //FM = 8
	//TCCR0B =0b0000 0011; //FM = 64
	//TCCR0B =0b0000 0100; //FM = 256
	TCCR0B =0b00000101; //FM = 1024
	#warning "C: Cargue la cuenta "
	TCNT0 = 131; //Cuenta del TMR0
	TIMSK0 |= 0b00000001; //Habilitacion particular
	sei(); //Habilitacion global
}