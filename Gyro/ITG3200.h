#ifndef _ITG3200_H
#define _ITG3200_H
#define _GYRO_ADDR 0x68
#define _GYRO_DATA 0x1D
#include "../TWI/twimaster.h"
#include "../USART/USART.h"

class ITG3200{
	public:
		const TWI twi = TWI(_GYRO_ADDR);
		ITG3200(void);
		void GetRotSpeeds(float data[3]);
		void PowerOn(void);
		void read_raw(char*d);
};

#endif
