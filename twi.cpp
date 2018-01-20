#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>

unsigned char address=0x20, write=0;
unsigned char write_data=0x52;

void LED1ON(void) {PORTA |= (1 << 7);}
void LED1OFF(void){PORTA &= ~(1 << 7);}
void TOGGLELED1(void) {if(bit_is_set(PORTC,7))PORTA &= ~(1 << 7); else PORTA |= (1 << 7);}

void LED2ON(void) {PORTA |= (1 << 6);}
void LED2OFF(void){PORTA &= ~(1 << 6);}
void TOGGLELED2(void) {if(bit_is_set(PORTC,6))PORTA &= ~(1 << 6); else PORTA |= (1 << 6);}

void TWI_init_master(void) // Function to initialize master
{
    TWBR=0x72;    // Bit rate
    TWSR=(0<<TWPS1)|(0<<TWPS0);    // Setting prescalar bits
    // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}

void TWI_start(void)
{
    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
    while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement
    LED1OFF();
}

void TWI_write_address(unsigned char data)
{
    TWDR=data; // Address & read instruction
    TWCR=(1<<TWINT)|(1<<TWEN); // Clear TWI interrupt flag, Enable TWI
    while(!(TWCR &(1<<TWINT))); // Wait till complete TWDR byte received
    while( (TWSR & 0xF8) != 0x18); // Check for then acknowledgement
    LED2OFF();
}

void TWI_write_data(unsigned char data)
{
    TWDR=data;    // put data in TWDR
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    while((TWSR & 0xF8) != 0x28); // Check for the acknoledgement
    _delay_ms(1000);
    TOGGLELED1();
    TOGGLELED2();
}

void TWI_stop(void)
{
    // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
}

int main(void)
{

    DDRA = 0xFF;

    //PORTA |= (1 << 6);
    //PORTA |= (1 << 7);
    //PORTA |= (1 << 3);
    LED1ON();
    _delay_ms(1000);

    sei();
    _delay_ms(2000);
    LED1OFF();

    TWI_init_master();    // Function to initialize TWI

    LED2ON();
    _delay_ms(1000);
    TWI_write_address(address+write); // Function to write address and data direction bit(write) on SDA

    while(1)
    {

        //LED1ON();
        TWI_start(); // Function to send start condition

        TWI_write_data(write_data);        // Function to write data in slave

        TWI_stop();    // Function to send stop condition

        _delay_ms(1000);    // Delay of 10 mili second
        LED1OFF();
        _delay_ms(1000);    // Delay of 10 mili second

    }

}
