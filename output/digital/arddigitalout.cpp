#include <output/arddigitalout.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>

#include <unistd.h>

#define SET_V 5

ArdDigitalOut::ArdDigitalOut(int bus, int address, int val) {
	_file = i2c_open_bus(bus);
	_address = address;
	set(val);
}

ArdDigitalOut::~ArdDigitalOut() {
	if (_file > 0) {
		close(_file);
	}
}
	
void ArdDigitalOut::set(int val) {
	if (!set_slave_addr(_file, _address, 0)) {
		i2c_smbus_write_byte_data(_file, SET_V, val);
	}
}
