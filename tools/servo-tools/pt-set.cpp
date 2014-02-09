#include <output/ardservo.h>
#include <output/pantilt.h>

#include <iostream>

#include <unistd.h>
#include <cstdlib>

using namespace std;

// pt-set <bus> <addr> <pan_idx> <tilt_idx> <pan> <tilt>
int main(int argc, char** argv) {
	if (argc != 7) {
		return 1;
	}
	
	int bus = atoi(argv[1]);
	int addr = (int)strtol(argv[2], 0, 0);
	int iPan = atoi(argv[3]);
	int iTilt = atoi(argv[4]);
	int pan = atoi(argv[5]);
	int tilt = atoi(argv[6]);
	
	PanTilt pt(new ArdServo(bus, addr, iPan), new ArdServo(bus, addr, iTilt));
	pt.panTo(pan);
	usleep(1);
	pt.tiltTo(tilt);
}
