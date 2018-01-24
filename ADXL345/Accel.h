#ifndef _ACCEL_H_
#define _ACCEL_H_  1

#include <avr/io.h>
#include <stdlib.h>
//#include "../i2c/i2cmaster.h"
#include "../TWI/twimaster.h"
#include "../USART/USART.h"
#include <stdio.h>

#define WRITE 0
#define READ 1
#define ACC_ADDR 0x53
#define POWER_CTL 0x2D
#define DATAX0 0x32 
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37

class Accel{
	public:
		const TWI twi = TWI(ACC_ADDR);
		Accel(void);
		void GetAccels(float data[3]);
		void Enter_meas_mode(void);
		void read_data(int[3]);
		void read_raw_data(char [6]);
		void set_offset(int*);
	private:
		void read_addr(char addr,char*val);
		void read_addr_twi(char addr,char*val);
		void write_addr(char addr,char value);

};
#endif
