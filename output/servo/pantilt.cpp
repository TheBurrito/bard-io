#include <output/pantilt.h>

PanTilt::PanTilt(Servo* pan, Servo* tilt) {
	_pan = pan;
	_tilt = tilt;
	_minPan = 0;
	_maxPan = 180;
	_minTilt = 0;
	_maxTilt = 180;
}

int PanTilt::pan(int dAngle) {
	int angle = _pan->getAngle() + dAngle;
	return panTo(angle);
}

int PanTilt::panTo(int angle) {
	if (angle < _minPan) angle = _minPan;
	else if (angle > _maxPan) angle = _maxPan;
	
	_pan->setAngle(angle);
	return angle;
}

int PanTilt::tilt(int dAngle) {
	int angle = _tilt->getAngle() + dAngle;
	return tiltTo(angle);
}

int PanTilt::tiltTo(int angle) {
	if (angle < _minTilt) angle = _minTilt;
	else if (angle > _maxTilt) angle = _maxTilt;
	
	_tilt->setAngle(angle);
	return angle;
}

int PanTilt::getPan() {
	return _pan->getAngle();
}

int PanTilt::getTilt() {
	return _tilt->getAngle();
}

void PanTilt::setLimits(int pMin, int pMax, int tMin, int tMax) {
	_minPan = pMin;
	_maxPan = pMax;
	_minTilt = tMin;
	_maxTilt = tMax;
	
	panTo(getPan());
	tiltTo(getTilt());
}
