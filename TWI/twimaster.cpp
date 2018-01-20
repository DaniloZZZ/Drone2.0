#include "twimaster.h"


//----------/
// Reads Accel Data about 3kHz (0.3ms)
//----------/
TWI::TWI(char addr) : DeviceAddress(addr)// Function to initialize master
{
    //TWBR=0x72;    					// Bit rate 100kHz
    TWBR=0x12;    						// Bit rate 400kHz
    TWSR=(0<<TWPS1)|(0<<TWPS0);			// Setting prescalar bits. Scaler = 1
    // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}
char TWI::ReadAddr(char addr){
    // read previously written value back from Accel
	// NOTE: original data type is unsigned char
	char val;
	this->start();
	this->write_data((this->DeviceAddress<<1)+0);
    this->write_data(addr);            
	this->start();
    this->write_data((this->DeviceAddress<<1)+1);   
    this->read_data(&val);     
	this->stop();
	return val;
}

void TWI::WriteAddr(char addr, char val){
	// write a value to given addreass of Accel 
	// TODO: check for errors, return a code
	this->start();
    this->write_data((this->DeviceAddress<<1)+0);     // set device address and write mode
	this->write_data(addr);
    this->write_data(val);                       
    this->stop(); 
}


void TWI::start(void)
{
    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
   // while(!(TWCR & (1<<TWINT))){
	while (!(TWCR & (1<<TWINT)));		// Wait till complete TWDR byte transmitted
	//}
	// Wait till start condition is transmitted
	//return((TWSR & 0xF8)!= 0x08);
}
void TWI::write_data(unsigned char data)
{
    TWDR=data;    // put data in TWDR
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	// TODO: Measure how many cycles i waste on waiting
}
void TWI::read_data(char * data){
	*(data) = (char)TWDR; 					// Set data
    TWCR|=(1<<TWINT)|(1<<TWEN);   		// Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT)));		// Wait till complete TWDR byte transmitted
	// TODO: Measure how many cycles i waste on waiting
}
void TWI::set_ack(char b){
	TWCR|=(b<<TWEA);
}
void TWI::stop(void)
{
    // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

