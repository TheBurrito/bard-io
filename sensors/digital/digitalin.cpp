#include <system/gpio.h>
#include <sensors/digitalin.h>

DigitalIn::DigitalIn(int gpio) {
	_gpio = new GPIO(gpio, 0);
}

DigitalIn::~DigitalIn() {
	delete _gpio;
}
	
int DigitalIn::read() {
	return _gpio->get();
}
