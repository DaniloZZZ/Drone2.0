#define F_CPU 16000000L
#include "Gyro/ITG3200.h"
#include "USART/USART.h"

#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
///#include <string.h>

int main(void){
	USART uart;
	ITG3200 gyro;
	char raw[6];
	float da[3];
	gyro.PowerOn();

	DDRD |= (1<<DDD2);
	while(1){
		//uart.put_str("\nX=");
		PORTD = 1<<2;
		//UDR0=(a);
		gyro.GetRotSpeeds(da);
		char str[10];
		sprintf(str,"%d,%d,%d\r",(int)da[0],(int)da[1],(int)da[2]);
		uart.put_str(str);
		PORTD = 0<<2;
		_delay_ms(20);
	} 
}
