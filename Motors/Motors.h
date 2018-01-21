#ifndef _MOTORS_H
#define _MOTORS_H 1

class Motors{
	public:
		const int*  Pins;
		Motors(int pins[4]);
		void SetSpeeds(int speeds [4]);
		void Calibrate(void);
};

#endif
