#include <avr/interrupt.h>
#include <avr/io.h>
#include "Motors.h"

ISR(TIMER1_COMPA_vect){
	PORTC = 0;
}
ISR(TIMER1_COMPB_vect){
	PORTC = 1;
}
ISR(TIMER1_OVF_vect){
	PORTC = 1;
}

Motors::Motors(int pins[4]) : Pins(pins){
	//__enable_interrupt(); /* set Global Interrupt Enable */
	DDRC |=1;
	OCR1AH = 0x00;
	OCR1BH = 0x03;

	OCR1BL = 0x00;
	OCR1AL = 0xFF;
	TCCR1A = 0x00;
	TCCR1B = 0b00000010;

	TIMSK1 = (1<<0)|(1<<1)|(1<<2);
	
	sei();
}

void Motors::Calibrate(void){
	for (short i = 0;i<4;i++){


	}
}

void Motors::SetSpeeds( int sp[4]){
	for (short i = 0;i<4;i++){

	}
}
