#include <output/ardservo.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>

#ifdef DEBUG
	#include <iostream>
#endif

#define SET_PI 1
#define SET_ANG 2

ArdServo::ArdServo(int bus, int uc_addr, int pwm_idx) {
	_file = i2c_open_bus(bus);
	_address = uc_addr;
	_pwm = pwm_idx;
}

int ArdServo::setAngle(const int angle) {
	_angle = angle;
	if (!set_slave_addr(_file, _address, 0)) {
		i2c_smbus_write_byte_data(_file, SET_PI, _pwm);
		#ifdef DEBUG
			std::cout << "Writing " << _pwm << " to register " << SET_PI << std::endl;
		#endif
	}
	if (!set_slave_addr(_file, _address, 0)) {
		i2c_smbus_write_byte_data(_file, SET_ANG, _angle);
		#ifdef DEBUG
			std::cout << "Writing " << _angle << " to register " << SET_ANG << std::endl;
		#endif
	}
	return 0;
}
