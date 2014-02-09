#ifndef pantilt_h_
#define pantilt_h_

#include <output/servo.h>

class PanTilt {
public:
	PanTilt(Servo* pan, Servo* tilt);
	
	int pan(int dAngle);
	int panTo(int angle);
	
	int tilt(int dTilt);
	int tiltTo(int angle);
	
	int getPan();
	int getTilt();
	
	void setLimits(int pMin, int pMax, int tMin, int tMax);
	
private:
	int _minPan, _maxPan, _minTilt, _maxTilt;
	Servo* _pan;
	Servo* _tilt;
};

#endif /*pantilt_h_*/
