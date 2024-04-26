#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// Define the segment codes for numbers 0-9
uint8_t segment_codes[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t paused = 0;

// Timer1 overflow interrupt service routine
ISR(TIMER1_OVF_vect) {
	if (!paused) {
		seconds++;
		if (seconds >= 60) {
			seconds = 0;
			minutes++;
			if (minutes >= 60) {
				minutes = 0;
			}
		}
	}
}

// External interrupt 1 service routine
ISR(INT1_vect) {
	paused = !paused;
}

void display_time() {
	// Display the minutes
	PORTD = (PORTD & 0x0F) | (segment_codes[minutes / 10] << 4);
	_delay_ms(5);
	PORTD = (PORTD & 0x0F) | (segment_codes[minutes % 10] << 4);
	_delay_ms(5);

	// Display the seconds
	PORTD = (PORTD & 0x0F) | (segment_codes[seconds / 10] << 4);
	_delay_ms(5);
	PORTD = (PORTD & 0x0F) | (segment_codes[seconds % 10] << 4);
	_delay_ms(5);
}

int main(void) {
	// Set PORTD as output
	DDRD = 0xFF;

	// Initialize Timer1
	TCCR1B |= (1 << CS12);  // Set prescaler to 256
	TIMSK1 |= (1 << TOIE1);  // Enable Timer1 overflow interrupt

	// Initialize external interrupt 1
	EICRA |= (1 << ISC10);  // Trigger on any logical change
	EIMSK |= (1 << INT1);  // Enable external interrupt 1

	sei();  // Enable global interrupts

	while (1) {
		display_time();
	}

	return 0;
}
