#ifndef USART_LIB
#define USART_LIB

// Check definition of CPU frequency
#ifndef F_CPU
#	error " Please define F_CPU frequency of your avr microcontroller"
#endif

#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>

class USART{
	public:
		unsigned int baud_rate;
		USART(); // Initializes at 38.4k baud rate
		char get_char(void);
		void put_char(char);
		float get_float(void);

//void put_str(char*);
		void put_str(char*);
		short get_str(char*); // provide a reference to string. returns length
};
#endif
