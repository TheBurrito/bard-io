#include <output/servo.h>

#include <unistd.h>

Servo::~Servo() {
	if (_file > 0) {
		close(_file);
	}
}

int Servo::getAngle() {
	return _angle;
}

Servo& Servo::operator=(const int angle) {
	setAngle(angle);
	return *this;
}

