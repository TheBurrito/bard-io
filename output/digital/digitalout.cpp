#include <output/digitalout.h>
#include <system/gpio.h>

DigitalOut::DigitalOut(int gpio, int val) {
	_gpio = new GPIO(gpio, 1, val);
}

DigitalOut::~DigitalOut() {
	delete _gpio;
}

void DigitalOut::set(int val) {
	_gpio->set(val);
}
