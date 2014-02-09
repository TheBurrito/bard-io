#include <output/ardservo.h>

#include <iostream>

#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 5) {
		return 1;
	}
	
	int bus = atoi(argv[1]);
	int addr = (int)strtol(argv[2], 0, 0);
	int idx = atoi(argv[3]);
	int ang = atoi(argv[4]);
	
	Servo* s = new ArdServo(bus, addr, idx);
	if (!s->isValid()) {
		cout << "Invalid Servo" << endl;
	} else {
		int ret = s->setAngle(ang);
		if (ret) {
			cout << "Error with setAngle: " << ret << endl;
		}
	}
	
	delete s;
}
