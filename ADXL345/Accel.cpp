#include "Accel.h"

Accel::Accel(void){
};

void Accel::Enter_meas_mode(void){
	TWI t =	this->twi;
	t.WriteAddr(POWER_CTL,1<<3);		// 3 byte is trigger for standby mode
}
void Accel::GetAccels(float data[3]){
	USART uart;
	int v[3];
	char* vp = (char*)v;
	char d[6];
	this->read_raw_data(vp);		// convert pointer to int into char and write all 6 bytes
	/*
	for(int i = 0;i<6;i++){
		uart.put_char(d[i]);
		_delay_ms(2);
	}
	*/
	for (short i=0;i<3;i++){
		data[i] = v[i]*0.039;
	}

	/*
	itoa(v[0],str,10);	
	uart.put_str(" x");
	uart.put_str(str);
	itoa(vp[1],str,10);	
	uart.put_str(" y");
	uart.put_str(str);
	itoa(v[2],str,10);	
	uart.put_str(" z");
	uart.put_str(str);
	uart.put_str(" ");
	*/
}
void Accel::read_data(int values[3]){
	char data[6];
	this->read_raw_data(data);
}
void Accel::read_raw_data(char* d){
	TWI twi;
	twi.start();
	twi.write_data((ACC_ADDR<<1)+0);			// Set address of accel
    twi.write_data(DATAX0);						// Write desired address. we will read all data
	twi.start();								// Repeated start, reading from accel	

    twi.write_data((ACC_ADDR<<1)+1);   
	twi.set_ack(1);								// Start sequental read
	twi.read_data(d);     //TODO: find out why first byte is always 0xA7;
	for(short i=0;i<5;i++){
		twi.read_data(d+i);     
	}
	twi.set_ack(0);								// Set ACK to 0 and read last value;
	twi.read_data(d+5);     
	// TODO: WARNING: next line freezes loop and new interrupt
	// never occures. If you have problem with i2c this can be the reason. 
	//twi.stop();
}

void Accel::write_addr(char addr, char val){
	TWI twi;
	// write a value to given addreass of Accel 
	twi.start();
    twi.write_data((ACC_ADDR<<1)+0);     // set device address and write mode
	twi.write_data(addr);
    twi.write_data(val);                       
    twi.stop(); 
}

void Accel::read_addr_twi(char addr,char *val){
	// NOTE: original data type is unsigned char
    // read previously written value back from Accel
	TWI twi;
	twi.start();
	twi.write_data((ACC_ADDR<<1)+0);
    twi.write_data(addr);            
	twi.start();
    twi.write_data((ACC_ADDR<<1)+1);   
    twi.read_data(val);     
	twi.stop();
}

void Accel::read_addr(char addr,char *val){
		unsigned char ret;
	USART uart;
        i2c_start((ACC_ADDR<<1)+I2C_WRITE);     // set device address and write mode
	uart.put_char(TWSR & 0xF8);
	_delay_ms(2);
        i2c_write(addr);                        // write address
	uart.put_char(TWSR & 0xF8);
	_delay_ms(2);
        i2c_rep_start((ACC_ADDR<<1)+I2C_READ);       // set device address and read mode
        ret = i2c_readNak();                    // read one byte
	uart.put_char(TWSR & 0xF8);
	_delay_ms(2);
	uart.put_char(ret);
	_delay_ms(2);
		*val = ret;
        i2c_stop();
}
