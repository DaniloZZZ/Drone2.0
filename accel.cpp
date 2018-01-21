#define F_CPU 16000000L
#include "ADXL345/Accel.h"
#include "USART/USART.h"
#include "Motors/Motors.h"

#include <avr/delay.h>
#include <string.h>


int main(void){
	USART uart;
	Accel acc;
	int mp[4] ={1,2,3,4};
	Motors Ms(mp);
	char raw[6];
	float a[3];

	char strnum [8];
	acc.Enter_meas_mode();
	DDRD |= (1<<DDD2);
	while(1){
		//uart.put_str("\nX=");
		PORTD = 1<<2;
		//UDR0=(a);
		acc.GetAccels(a);
		float roll = atan2(a[1], a[2]) * 180/3.14;
		float pitch = atan2(-a[0], sqrt(a[1]*a[1] + a[2]*a[2])) * 180/3.14;
		char str[10];

		/*
		dtostrf(roll,6,4,str);
		uart.put_str(" roll:");
		uart.put_str(str);

		dtostrf(pitch,6,4,str);
		uart.put_str(" pitch:");
		uart.put_str(str);
		uart.put_str("\n");
		*/
		PORTD = 0<<2;
		_delay_ms(500);
	} 
}
