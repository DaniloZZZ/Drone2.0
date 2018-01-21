#include "Motors.h"
static int OneMs = 2000;
unsigned int sped[MCNT] = {1};
unsigned int pin[MCNT] = {0};
unsigned int pinport[4] = {PORTC,PORTC,PORTC,PORTC};
static int idx = 0;
int val = 0;

ISR(TIMER1_COMPA_vect){
	//TCNT1H=0;						// Reset Timer every 20ms
	//TCNT1L=0;
}

ISR(TIMER1_COMPB_vect){
	if(idx==MCNT) { 
		idx=0;
		val = 0;
		OCR1BH = 0x90;					// Set OCRB to shot on next cycle, 20ms after start
		OCR1BL = 0x3F;
		for(short i=0;i<MCNT;i++){
			PORTC &= ~(1<<pin[i]);		// Turn off all
		}
   	}
	else{
	val +=OneMs+sped[idx]*(2000/256.0/256.);
	UDR0 = val>>8;
	
	if(idx==0){
		TCNT1H=0;						// Reset Timer every 20ms
		TCNT1L=0;
	}
	OCR1BH = val>>8;
	OCR1BL = (255&val);

	for (short i=0;i<MCNT;i++){
		if(i==idx)
			PORTC |= (1<<pin[idx]); 	// Turn on desired pin motor
		else
			PORTC &= ~(1<<pin[i]);		// Turn off all else (previous is enogh though)
	}
	idx++;
	}
}

ISR(TIMER1_OVF_vect){
	//PORTC = 1;
	//TIFR1 = (1<<1);
}


Motors::Motors() {
	//__enable_interrupt(); /* set Global Interrupt Enable */
	
	OCR1BH = 0x90;					// Set OCRA to trigger every 20ms
	OCR1BL = 0x3F;

	TCCR1A = 0x00;
	TCCR1B = 0b00000010;

	TIMSK1 = (1<<0)|(1<<1)|(1<<2);
	this->SpeedsVals = sped;
	this->Pins = pin;
	sei();
}

void Motors::ConfPins(void){
	for (short i=0;i<MCNT;i++){
		DDRC |= (1<<(this->Pins[i]));
	}
}

void Motors::Calibrate(void){
	for (short i = 0;i<MCNT;i++){
		this->SpeedsVals[i]=0xFFFF;
		UDR0 =0xff;
	}
	// TODO: make this work on interrupts to init drone faster
	_delay_ms(1500);
	for (short i = 0;i<MCNT;i++){
		this->SpeedsVals[i]=0x00;
		UDR0 =0x0000;
	}
	_delay_ms(1500);
}


void Motors::SetSpeedsP( int * const sp)const{
	//this->SpeedsVals = sp;
	for (short i = 0;i<4;i++){

	}
}
