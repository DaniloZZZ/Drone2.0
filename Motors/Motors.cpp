#include "Motors.h"

ISR(TIMER1_COMPA_vect){
	PORTC = 0;
}
ISR(TIMER1_COMPB_vect){
	//PORTC = 1;
}
ISR(TIMER1_OVF_vect){
	PORTC = 1;
	TIFR1 = (1<<1);
}

Motors::Motors(int pins[4]) : Pins(pins){
	//__enable_interrupt(); /* set Global Interrupt Enable */
	DDRC |=1;
	OCR1AH = 0x9C;					// Set OCRA to trigger every 20ms
	OCR1AL = 0x3F;

	TCCR1A = 0x00;
	TCCR1B = 0b00000101;

	TIMSK1 = (1<<0)|(1<<1)|(1<<2);
	
	sei();
}

void Motors::Calibrate(void){
	int spf[4] = {0xFF,0xFF,0xFF,0xFF};
	int spm[4] = {0x00,0x00,0x00,0x00};
	for (short i = 0;i<4;i++){
		this->SetSpeeds(spf);		// Full Throttle
		_delay_ms(1500);
		this->SetSpeeds(spm);		// Minimum Throttle
		_delay_ms(1000);
		// TODO: make this work on interrupts to init drone faster
	}
}

void Motors::SetSpeeds( int sp[4]){
	for (short i = 0;i<4;i++){

	}
}
