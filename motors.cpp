#define F_CPU 16000000L
#include "Motors/Motors.h"
#include "USART/USART.h"

#include <avr/delay.h>
#include <string.h>
#include <avr/io.h>

int main(void){
	USART uart;
	int mp[4] ={1,2,3,4};
	Motors ms(mp);
	char a;
	while(1){
		//uart.put_str("\nX=");
		PORTD = 1<<2;
		a= TCNT1L;
		UDR0=TCNT1H;
		PORTD = 0<<2;
		_delay_ms(50);
	} 
}
