#include <sensors/arddigitalin.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>

#include <unistd.h>

#define GET_ST 4

ArdDigitalIn::ArdDigitalIn(int bus, int address, int pin) {
	_file = i2c_open_bus(bus);
	_address = address;
	_pin = pin;
}

ArdDigitalIn::~ArdDigitalIn() {
	if (_file > 0) {
		close(_file);
	}
}

int ArdDigitalIn::read() {
	if (_file > 0) {
		if (!set_slave_addr(_file, _address, 0)) {
			//Tell it that we want to read a pin
			i2c_smbus_write_byte_data(_file, GET_ST, _pin);
			return i2c_smbus_read_byte(_file);
		}
	}
}
