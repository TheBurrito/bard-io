#include <sensors/srf08.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>

#define REG_W_COMMAND 0x00

#define REG_R_VERSION 0x00
#define REG_R_LIGHT 0x01
#define REG_R_1_H 0x02
#define REG_R_1_L 0x03

SRF08::SRF08(int bus, int address, SRF08::Units units):
		_units(units), _address(address) {
	_file = i2c_open_bus(bus);
}

int SRF08::getVersion() {
	return i2c_smbus_read_byte_data(_file, REG_R_VERSION);
}

int SRF08::getLight() {
	return i2c_smbus_read_byte_data(_file, REG_R_LIGHT);
}

void SRF08::startRange() {
	if (!set_slave_addr(_file, _address, 0)) {
		i2c_smbus_write_byte_data(_file, REG_W_COMMAND, _units);
	}
}

int SRF08::getRange() {
	if (set_slave_addr(_file, _address, 0)) {
		return -1;
	}
	
	int ret = i2c_smbus_read_byte_data(_file, REG_R_1_H) << 8;
	ret += i2c_smbus_read_byte_data(_file, REG_R_1_L);
	
	return ret;
}

bool SRF08::isValid() {
	return _file > 0;
}

bool SRF08::isReady() {
	if (set_slave_addr(_file, _address, 0)) {
		return false;
	}
	
	return i2c_smbus_read_byte_data(_file, REG_R_VERSION) != -1;
}
