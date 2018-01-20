#define F_CPU 16000000L

#include "USART/USART.h"


int main(void){
	USART uart;
	DDRD |= (1<<DDD2);
	PORTD ^= 1<<DDD2;
	char st[32]="asdfjkl;asdfjkl;asdfjkl;asdfjkl";
	uart.put_str("Hello Dail's Lenovo!\n Provide a command:\n");
	int l =0;
	while(1){
		l = uart.get_str(st);
		uart.put_str("\ngocha:\n");
		uart.put_str(st);
	}


}

