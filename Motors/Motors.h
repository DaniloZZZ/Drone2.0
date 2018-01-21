#ifndef _MOTORS_H
#define _MOTORS_H 1
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>

class Motors{
	public:
		const int*  Pins;
		Motors(int pins[4]);
		void SetSpeeds(int speeds [4]);
		void Calibrate(void);
};

#endif
