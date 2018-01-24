#include "ITG3200.h"

void swap(char* a,char*b){
	char c = *a;
	*a = *b;
	*b = c;
}
ITG3200::ITG3200(void){
}
void ITG3200::PowerOn(){
	TWI t =	this->twi;
	t.WriteAddr(0x3E,0x01);		// Power-up
	t.WriteAddr(0x16,0x18);		// Full scale, 2000dps
	t.WriteAddr(0x16,(3<<3)|(3));		// Full scale, 2000dps
}

void ITG3200::GetRotSpeeds(float data[3]){
	USART uart;
	int v[3];
	char* vp = (char*)v;
	char d[6];
	this->read_raw(vp);		// convert pointer to int into char and write all 6 bytes
	/*
	for(int i = 0;i<6;i++){
		uart.put_char(d[i]);
		_delay_ms(2);
	}
	*/
	//swap(vp,vp+1);
	//swap(vp+2,vp+3);
	//swap(vp+4,vp+5);
	for (short i=0;i<3;i++){
		data[i] = v[i]*0.0619;
	}
}

void ITG3200::read_raw(char*d){
	TWI twi;
	twi.start();
	twi.write_data((_GYRO_ADDR<<1)+0);			// Set address of accel
    twi.write_data(_GYRO_DATA);					// Write desired address. we will read all data
	twi.start();								// Repeated start, reading from accel	

    twi.write_data((_GYRO_ADDR<<1)+1);   
	twi.set_ack(1);								// Start sequental read
	//twi.read_data(d);     //TODO: find out why first byte is always 0xA7;
	for(short i=0;i<5;i++){
		twi.read_data(d+i);     
	}
	twi.set_ack(0);								// Set ACK to 0 and read last value;
	twi.read_data(d+5);     
	// TODO: WARNING: next line freezes loop and new interrupt
	// never occures. If you have problem with i2c this can be the reason. 
	//twi.stop();
}
