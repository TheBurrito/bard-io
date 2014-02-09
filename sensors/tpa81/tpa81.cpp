#include <sensors/tpa81.h>
#include <system/i2c.h>

#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>

#ifdef DEBUG
	#include <iostream>
#endif

#define REG_W_COMMAND 		0x00
#define REG_W_SERVORANGE 	0x01

#define REG_R_SOFTREV		0x00
#define REG_R_AMBIENT		0x01
#define REG_R_TEMP1			0x02
#define REG_R_TEMP2			0x03
#define REG_R_TEMP3			0x04
#define REG_R_TEMP4			0x05
#define REG_R_TEMP5			0x06
#define REG_R_TEMP6			0x07
#define REG_R_TEMP7			0x08
#define REG_R_TEMP8			0x09


TPA81::TPA81(int bus, int address, uint8_t reverse):
		_address(address) {
	_file = i2c_open_bus(bus);
	_reverse = reverse;
}

bool TPA81::isValid() {
	return _file > 0;
}

uint8_t readData(int file, int address, int reg) {
	if (!set_slave_addr(file, address, 0)) {
		return i2c_smbus_read_byte_data(file, reg);
	}
	return -1;
}

void TPA81::update() {
	#ifdef DEBUG
		std::cout << "TPA81::update()" << std::endl;
	#endif
	
	if (!set_slave_addr(_file, _address, 0)) {
		_ambient = i2c_smbus_read_byte_data(_file, REG_R_AMBIENT);
		
		int j;
		for (int i = REG_R_TEMP1; i <= REG_R_TEMP8; ++i) {
			j = i - REG_R_TEMP1;
			
			if (_reverse) {
				j = 7 - j;
			}
			
			_temps[j] = readData(_file, _address, i);
			
			#ifdef DEBUG
				std::cout << ((int)_temps[j]) << " ";
			#endif
		}
		
		#ifdef DEBUG
			std::cout << std::endl;
		#endif
	}
}

uint8_t TPA81::getAmbient() {
	return _ambient;
}

uint8_t* TPA81::getTemps() {
	#ifdef DEBUG
		std::cout << "TPA81::getTemp()" << std::endl;
	#endif
	
	uint8_t *ret = (uint8_t*)malloc(8 * sizeof(uint8_t*));
	for (int i = 0; i < 8; ++i) {
		ret[i] = _temps[i];
	}
	return ret;
}
