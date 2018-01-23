#define F_CPU 16000000L
#include "Motors/Motors.h"
#include "USART/USART.h"

#include "ADXL345/Accel.h"
#include <avr/delay.h>
#include <string.h>
#include <avr/io.h>

float roll, _roll,pitch,_pitch,mod,_mod;
const float al = 0.1;
int speed, _speed;

int main(void){
	char raw[6];
	float a[3];
	char strnum [8];
	char str[20];
	USART uart;
	Accel acc;
	acc.Enter_meas_mode();
	Motors motors;
	motors.ConfPins();

	_delay_ms(1000);
	motors.Calibrate();
	DDRD |= (1<<DDD2);

	while(1){
		PORTD = 1<<2;
		acc.GetAccels(a);
		mod = sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
		roll = atan2(a[1], a[2]) * 180/3.14;
		pitch = atan2(-a[0], sqrt(a[1]*a[1] + a[2]*a[2])) * 180/3.14;
		// Th copter probably will not be at angles bigger than 0.3
		// TODO: measure excec time and find time consuming parts
		mod = _mod*(1-al) +al*mod;
		_mod = mod;
		pitch = _pitch*(1-al) +al*pitch;
		_pitch = pitch;
		for (short i = 0;i<MCNT;i++){
			speed = (0x3040-(int)(pitch*(0x5030/70)));
			motors.SpeedsVals[i]=speed;
		}
		sprintf(str,"%d,%d,%d,%d\r",(int)(mod*20),speed/100,(int)(pitch*5),(int)(20*a[0]));
		uart.put_str(str);
/*
		itoa(speed,str,10);
		uart.put_str("");
		uart.put_str(str);
		_delay_ms(2);

		dtostrf(mod,6,4,str);
		uart.put_str(",");
		uart.put_str(str);

		dtostrf(roll,6,4,str);
		uart.put_str(",");
		uart.put_str(str);

		dtostrf(pitch,6,4,str);
		uart.put_str(",");
		uart.put_str(str);
		uart.put_str("\n");
		*/
		PORTD = 0<<2;
		_delay_ms(3);
	} 
}
