#define F_CPU 16000000L
#include "Motors/Motors.h"
#include "USART/USART.h"
#include "Gyro/ITG3200.h"
#include "ADXL345/Accel.h"

#include <avr/delay.h>
#include <string.h>
#include <avr/io.h>

float roll, _roll,pitch,_pitch,mod,_mod,sx;
float pm,dm;
const float al = 0.1;
int speed, _speed,scale;

int main(void){
	float a[3],da[3], dp;
	char strnum [8];
	char str[20];
	USART uart;
	Accel acc;
	ITG3200 gyro;
	Motors motors;

	acc.Enter_meas_mode();
	gyro.PowerOn();
	motors.ConfPins();

	_delay_ms(1000);
	motors.Calibrate();
	DDRD |= (1<<DDD2);
	pm = 1/3.;
	dm = 1/3.;
	scale = 0x4000;

	while(1){
		PORTD = 1<<2;
		acc.GetAccels(a);
		mod = sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
		roll = atan2(a[1], a[2]);
		pitch = atan2(-a[0], sqrt(a[1]*a[1] + a[2]*a[2]));
		// The copter probably will not be at angles bigger than 0.3
		// TODO: measure excec time and find time consuming parts
		gyro.GetRotSpeeds(da);

		mod = _mod*(1-al) +al*mod;
		_mod = mod;
		pitch = _pitch*(1-al) +al*pitch;
		dp = pitch-_pitch;
		_pitch = pitch;
		//for (short i = 0;i<MCNT;i++){
			//speed = 0x33040*(1-(pitch/10)-da[1]/10000);
		dp += da[1];
		sx = 3.*(pm*pitch + dm*0.5*(dp));
		if(abs(sx)>=1)
			sx=1;
		motors.SpeedsVals[0]=scale*(1-sx);
		motors.SpeedsVals[1]=scale*(1+sx);
		//}

		sprintf(str,"%d,%d,%d\r",(int)(scale*sx),(int)(scale*pm*pitch),(int)(scale*dm*dp));
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
