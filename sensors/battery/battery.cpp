#include <sensors/battery.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>

#define REG_W_COMMAND 0x00

#define REG_W_AN 0x03

Battery::Battery(int bus, int address, int an, float factor, float railV, int bits) :
    _address(address), _an(an) {
  _adj = railV * factor / bits;
  _file = i2c_open_bus(bus);
}

void Battery::startRead() {
  if (!set_slave_addr(_file, _address, 0)) {
		i2c_smbus_write_byte_data(_file, REG_W_AN, _an);
	}
}

float Battery::getVoltage() {
  if (!set_slave_addr(_file, _address, 0)) {
    int t = i2c_smbus_read_byte(_file);
    t += i2c_smbus_read_byte(_file);
    
    return (double)t * _adj;
	}
	
	return -1;
}

bool Battery::isValid() {
	return _file > 0;
}
