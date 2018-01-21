#ifndef _MOTORS_H
#define _MOTORS_H 1
#define MCNT 1

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>

extern "C" void TIMER1_COMPA_vect(void) __attribute__ ((signal));

class Motors{
	public:
		unsigned int*  Pins;
		unsigned int * SpeedsVals;
		Motors();
		void ConfPins(void);
		void SetSpeedsP(int * const speeds) const;
		void Calibrate(void);

		friend void TIMER1_COMPA_vect(void);
};

#endif
