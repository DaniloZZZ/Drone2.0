// Includes
//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include "print.h"
//Macros and defines
#define BAUD 19200
#define F_CPU 16000000L


#define MYUBRR F_CPU/16/BAUD-1
// Create a "Stream" for output
// http://efundies.com/avr-and-printf/
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

int main( void ) {
    // define some local variables
    uint8_t myvalue;
 
    // setup our stdio stream
    stdout = &mystdout;
 
    // fire up the usart
    usart_init ( MYUBRR );
 
    // dump some strings to the screen at power on
    myvalue = 64;
    printf("Here is myvalue as an unsigned integer: %d\n", myvalue);
    printf("Here is myvalue as a char: %c\n", myvalue);
    printf("Here is myvalue in hex: 0x%X\n", myvalue);
    printf("Here is myvalue in octal: %o\n", myvalue);
 
    // main loop
    while(true) {
        // do nothing
    }
}
// ********************************************************************************
// usart Related
// ********************************************************************************
void usart_init( uint16_t ubrr) {
    // Set baud rate
    UBRRH = (uint8_t)(ubrr>>8);
    UBRRL = (uint8_t)ubrr;
    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
    // Set frame format: 8data, 1stop bit
    UCSRC = (1<<URSEL)|(3<<UCSZ0);
}
void usart_putchar(char data) {
    // Wait for empty transmit buffer
    while ( !(UCSRA & (_BV(UDRE))) );
    // Start transmission
    UDR = data; 
}
char usart_getchar(void) {
    // Wait for incoming data
    while ( !(UCSRA & (_BV(RXC))) );
    // Return the data
    return UDR;
}
unsigned char usart_kbhit(void) {
    //return nonzero if char waiting polled version
    unsigned char b;
    b=0;
    if(UCSRA & (1<<RXC)) b=1;
    return b;
}
void usart_pstr(char *s) {
    // loop through entire string
    while (*s) { 
        usart_putchar(*s);
        s++;
    }
}

int usart_putchar_printf(char var, FILE *stream) {
	    if (var == '\n') usart_putchar('\r');
	    usart_putchar(var);
	    return 0;
}
