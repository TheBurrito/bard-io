#ifndef servo_h_
#define servo_h_

class Servo {
public:	
	~Servo();
	virtual int setAngle(const int angle) = 0;
	int getAngle();
	
	Servo& operator=(const int angle);
	operator int() { return _angle; }
	
	bool isValid() { return _file > 0; }
	
protected:
	int _angle;
	int _file;
};

#endif /*servo_h_*/
