include <avr/io.h>
#define F_CPU 16000000UL //16MHz

uint8_t i = '0' ;

void UARTInit(void) {
    UBRR0H = 0;
    UBRR0L = 25; //baud rate 38.4k
    //UBRR0L = 103; //baud rate 9600

    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
    UCSR0C |= (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00); //8 bit, 1 stop bit
}

void UARTSend(uint8_t data) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

int main(void) {
	//Configure as output
	DDRD |= (1<<DDD2);
	UARTInit();
	while(1) {
		i++;
		PORTD ^= 1<<DDD2;
		UARTSend(i);
	}
}
