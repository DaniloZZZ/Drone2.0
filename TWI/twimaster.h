#ifndef _TWI_H
#define _TWI_H 1
#include <avr/io.h>
#define i2c_PORT	PORTC		// Порт где сидит нога TWI
#define i2c_DDR		DDRC
#define i2c_SCL		0		// Биты соответствующих выводов
#define i2c_SDA		1

class TWI{
	public:
		const char DeviceAddress;
		char ReadAddr(char addr);
		void WriteAddr(char addr, char val);

		TWI(char addr = 0x16) ;
		void start(void);
		void write_data(unsigned char data);
		void read_data(char *data);
		void set_ack(char);
		void stop(void);
	
};
#endif
