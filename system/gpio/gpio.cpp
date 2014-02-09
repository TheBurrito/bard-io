#include <system/gpio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>

static char buf[50];

int setDirection(int gpio, int out) {
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	int dir = open(buf, O_WRONLY);
	if (dir > 0) {
		int len = sprintf(buf, "%s", out ? "out" : "in");
		write(dir, buf, len);
		close(dir);
		return 1;
	}
	
	return 0;
}

int openGPIO(int gpio) {
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	return open(buf, O_RDWR);
}

GPIO::GPIO(int gpio) {
	init(gpio, 1, 0);
}

GPIO::GPIO(int gpio, int out) {
	init(gpio, out, 0);
}

GPIO::GPIO(int gpio, int out, int val) {
	init(gpio, out, val);
}

void GPIO::init(int gpio, int out, int val) {
	_gpio = gpio;
	_file = openGPIO(gpio);
	
	setDirection(gpio, out);
	set(val);
}

GPIO::~GPIO() {
	if (_file > 0) {
		close(_file);
	}
}

void GPIO::set(int val) {
	int len = sprintf(buf, "%d", val);
	write(_file, buf, len);
}

int GPIO::get() {
	int len = read(_file, buf, 50);
	return atoi(buf);
}
