#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#define LOWER 77
#define UPPER 107
#define UNPLUGGED 2

#define UP    7
#define DOWN  2
#define LEFT  1
#define RIGHT 0

#define SET_BIT(X,Y)  X |= (1 << (Y))
#define CLR_BIT(X,Y)  X &= (~(1 << (Y)))

int main(void) {
	unsigned char analog;
	// unsigned char i,n;
	
        // make input
	DDRA = 0x00; 
	DDRB = 0x00;

        // set outputs to low
	PORTA = 0x00;
	PORTB = 0x00;

	ADMUX = 0x00; // set reference voltage to vcc

	ADCSRA |= _BV(7); // enable ADC
	ADCSRB |= _BV(4); // enable left adjust mode

	wdt_enable(WDTO_30MS); // enable watchdog timer

	for(;;) {
		wdt_reset();
		ADMUX |= _BV(0);  // set muxer to ADC1
		ADCSRA |= _BV(6); // start conversion

		while (ADCSRA & _BV(6)) {
			// wait for conversion to finish
		}
		analog = ADCH >> 1;
		
		if (analog < UNPLUGGED) {
			// PORTA = porta_mask & ~(0);
			// PORTA |= _BV(UP);
			// PORTB |= _BV(DOWN);
			CLR_BIT(DDRA, UP);
			CLR_BIT(DDRB, DOWN);
			 
		} else if (analog < LOWER) {
			// PORTB &= ~(_BV(DOWN));
			// PORTA |= _BV(UP);
			SET_BIT(DDRB, DOWN);
			CLR_BIT(DDRA, UP);
			
			
		} else if (analog > UPPER) {
			// PORTA &= ~(_BV(UP));
			// PORTB |= _BV(DOWN);
			SET_BIT(DDRA, UP);
			CLR_BIT(DDRB, DOWN);
		} else {
			// PORTA |= (_BV(UP));
			// PORTB |= (_BV(DOWN));
			CLR_BIT(DDRA, UP);
			CLR_BIT(DDRB, DOWN);			
		}

		ADMUX = 0x00;  // set muxer to ADC0
		ADCSRA |= _BV(6); // start conversion

		while (ADCSRA & _BV(6)) {
			// wait for conversion to finish
		}
		analog = ADCH >> 1;
		
		
		if (analog < UNPLUGGED) {
			// PORTB |= (_BV(RIGHT) | _BV(LEFT));
			CLR_BIT(DDRB, RIGHT);
			CLR_BIT(DDRB, LEFT);
		} else if (analog < LOWER) {
			// PORTB &= ~(_BV(RIGHT));
			// PORTB |= _BV(LEFT);
			SET_BIT(DDRB, RIGHT);
			CLR_BIT(DDRB, LEFT);
		} else if (analog > UPPER) {
			// PORTB &= ~(_BV(LEFT));
			// PORTB |= _BV(RIGHT);
			SET_BIT(DDRB, LEFT);
			CLR_BIT(DDRB, RIGHT);
		} else {
			// PORTB |= (_BV(RIGHT) | _BV(LEFT));
			CLR_BIT(DDRB, LEFT);
			CLR_BIT(DDRB, RIGHT);
		}
	}
}

