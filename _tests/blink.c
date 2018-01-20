
#include <avr/io.h>
#define F_CPU 16000000L
#include <avr/delay.h>

int main(void) {
	
	//Configure as output
	DDRD |= (1<<DDD2);
	while(1){
		PORTD = 0<<2;
		_delay_ms(1000);
		PORTD = 1<<2;
		_delay_ms(1000);
	}
}
