#include <system/i2c.h>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <cstdio>

int set_slave_addr(int file, int address, int force)
{
	/* With force, let the user read from/write to the registers
	   even when a driver is also running */
	if (ioctl(file, force ? I2C_SLAVE_FORCE : I2C_SLAVE, address) < 0) {
		return -errno;
	}

	return 0;
}

int i2c_open_bus(int bus) {
	char file[15];
	sprintf(file, "/dev/i2c-%d", bus);
	
	int fd = open(file, O_RDWR);
	if (fd < 1) {
		return -errno;
	}
	
	return fd;
}
