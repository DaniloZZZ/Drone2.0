#define F_CPU 16000000L
#include "Motors/Motors.h"
#include "USART/USART.h"

#include <avr/delay.h>
#include <string.h>
#include <avr/io.h>

int main(void){
	USART uart;
	int mp[4] ={1,2,3,4};
	char a;
	int spd = 0;
	char d = 1;
	Motors motors;
	motors.ConfPins();
	motors.Calibrate();

	_delay_ms(1500);
	while(1){
		//uart.put_str("\nX=");
		PORTD = 1<<2;
		a=TCNT1L;
		UDR0=TCNT1H;
		for (short i = 0;i<MCNT;i++){
			motors.SpeedsVals[i]=spd;
		}
		spd+=d*300;
		if((d>0)&&(spd>0x6000)){
			d=-1;
		}
		else{
			if(spd<0){
				spd = 2;
				d=1;
			}
		}

		PORTD = 0<<2;
		_delay_ms(50);
	} 
}
