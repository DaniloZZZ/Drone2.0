#include "USART.h"

USART::USART(){
	UBRR0H = 0;
	UBRR0L = 25; //baud rate 38.4k
	//UBRR0L = 103; //baud rate 9600

	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00); //8 bit, 1 stop bit
}
char USART::get_char(){
	while(!(UCSR0A & (1<<RXC0))); // wait for data
	return UDR0;
}
void USART::put_char(char c){
	while(!(UCSR0A & (1<<UDRE0))); // while "buffer empty" flad is not set
	UDR0 = c;
}

void USART::put_str(char *s) {
	// loop through entire string
	while (*s) { 
		this->put_char(*s);
		s++;
	}
}
short USART::get_str(char*s){
	short i =-1;
	do{
		i++;
		s[i]=this->get_char();
	}while((s[i]!='\n')&&(s[i+1]!='\0'));
	return i;
}
