#include <output/l298n.h>
#include <system/gpio.h>

#include <cstring>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#ifdef DEBUG
	#include <iostream>
#endif

static char buf[50];

/*
	Returns 0 if the gpio is exported, anything else if there was a problem
	getting the gpio exported.
*/

int checkPWMdev(int pwm) {
	sprintf(buf, "/dev/pwm%d", pwm);
	int res = 0;
	
	int fd = open(buf, O_WRONLY);
	if (fd == -1) {
		res = -1;
	} else {
		close(fd);
	}
	
	return res;
}

int openPWM(int pwm) {
	sprintf(buf, "/dev/pwm%d", pwm);
	int fd = open(buf, O_WRONLY);
	return fd;
}

void writeint(int fd, int val) {
	#ifdef DEBUG
		std::cout << "writeint(" << fd << ", " << val << ")" << std::endl;
	#endif
	
	int len = sprintf(buf, "%d", val);
	write(fd, buf, len);
}

L298N::L298N(int in1, int in2, int in3, int in4, int ena, int enb) {
	_valid = true; //innocent until proven guilty
	
	/*if (checkGPIOexport(in1) || checkGPIOexport(in2) || checkGPIOexport(in3) || checkGPIOexport(in4)) {
		//Problem with one of the GPIOs
		_valid = false;
	}
	
	if (checkPWMdev(ena) || checkPWMdev(enb)) {
		//Problem with one of the PWM devices in /dev
		_valid = false;
	}*/
	
	/*if (setGPIOout(in1) || setGPIOout(in2) || setGPIOout(in3) || setGPIOout(in4)) {
		//couldn't set gpio to output
		_valid = false;
	}
	
	_fd1 = openGPIO(in1);
	if (_fd1 == -1) {
		_valid = false;
	}
	
	_fd2 = openGPIO(in2);
	if (_fd2 == -1) {
		close(_fd1);
		_valid = false;
	}
	
	_fd3 = openGPIO(in3);
	if (_fd3 == -1) {
		_valid = false;
	}
	
	_fd4 = openGPIO(in4);
	if (_fd4 == -1) {
		_valid = false;
	}*/
	
	_in1 = new GPIO(in1, 1, 1);
	_in2 = new GPIO(in2, 1, 0);
	_in3 = new GPIO(in3, 1, 1);
	_in4 = new GPIO(in4, 1, 0);
	
	_fda = openPWM(ena);
	if (_fda == -1) {
		_valid = false;
	}
	
	_fdb = openPWM(enb);
	if (_fdb == -1) {
		_valid = false;
	}
	
	//set initial "safe" condition
	set(1, 0, 1, 0, 0, 0);
}

L298N::~L298N() {
	#ifdef DEBUG
		std::cout << "~L298N" << std::endl;
	#endif
	
	delete _in1;
	delete _in2;
	delete _in3;
	delete _in4;
	
	if (_fda > -1) {
		close(_fda);
	}
	
	if (_fdb > -1) {
		close(_fdb);
	}
}

void L298N::set(int in1, int in2, int in3, int in4, int ena, int enb) {
	if (!_valid) {
		return;
	}
	
	#ifdef DEBUG
		std::cout << "Set(" << in1 << ", " << in2 << ", " << in3 << ", " << in4 << ", " << ena << ", " << enb << ")" << std::endl;
	#endif
	
	/*writeint(_fd1, in1);
	writeint(_fd2, in2);
	writeint(_fd3, in3);
	writeint(_fd4, in4);*/
	_in1->set(in1);
	_in2->set(in2);
	_in3->set(in3);
	_in4->set(in4);
	
	writeint(_fda, ena);
	writeint(_fdb, enb);
}

bool L298N::isValid() {
	return _valid;
}
