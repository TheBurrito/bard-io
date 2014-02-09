#ifndef ardservo_h_
#define ardservo_h_

#include <output/servo.h>

class ArdServo : public Servo {
public:
	ArdServo(int bus, int uc_addr, int pwm_idx);
	
	virtual int setAngle(const int angle);
	
private:
	int _address;
	int _pwm;
};

#endif /*ardservo_h_*/
