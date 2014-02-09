#include <sensors/rotaryencoder.h>

/*#include <cstring>
#include <cstdio>*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <cstdlib>

#include <linux/input.h>

RotaryEncoder::RotaryEncoder(const char* dev) {
	_file = open(dev, O_RDWR);
	
	struct input_absinfo abs_feat;
	if(!ioctl(_file, EVIOCGABS(0), &abs_feat)) {
        _val = abs_feat.value;
    }
}

RotaryEncoder::~RotaryEncoder() {
	if (_file > 0) {
		close(_file);
	}
}

int RotaryEncoder::value(int timeout_uS) {
	struct input_event ie;
	ie.type = 0;
	
	if (timeout_uS > 0) {
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = timeout_uS;
		
		fd_set set;
		FD_ZERO(&set);
		FD_SET(_file, &set);
		
		while (ie.type != EV_ABS) {
			int rv = select(_file + 1, &set, 0, 0, &timeout);
		
			if (rv > 0) {
				read(_file, &ie, sizeof(struct input_event));
			} else if (rv == 0) {
				return _val;
			}
		}
	} else {
		while (ie.type != EV_ABS) {
			read(_file, &ie, sizeof(struct input_event));
		}
	}
	
	_val = ie.value;
	return ie.value;
}

struct input_event* RotaryEncoder::event() {
	struct input_event* ie = (struct input_event*)malloc(sizeof(struct input_event));
	read(_file, ie, sizeof(struct input_event));
	return ie;
}
