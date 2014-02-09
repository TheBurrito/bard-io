#include <output/dualmotorl298n.h>
#include <output/l298n.h>
#include <cstdlib>

#ifdef DEBUG
	#include <iostream>
#endif

DualMotorL298N::DualMotorL298N(int in1, int in2, int in3, int in4, int ena, int enb) {
	out = new L298N(in1, in2, in3, in4, ena, enb);
}

DualMotorL298N::~DualMotorL298N() {
	out->set(1, 0, 1, 0, 0, 0);
	delete out;
}

bool DualMotorL298N::brake() {
	if (!out->isValid()) {
		return false;
	}
	
	out->set(0, 0, 0, 0, 10000, 10000);
	return true;
}

bool DualMotorL298N::drive(int a, int b) {
	if (!out->isValid()) {
		return false;
	}
	
	int adir = a >= 0;
	int bdir = b >= 0;
	int aspd = abs(a);
	int bspd = abs(b);
	
	#ifdef DEBUG
		std::cout << "adir:" << adir << " bdir:" << bdir;
		std::cout << " aspd:" << aspd << " bspd:" << bspd << std::endl;
	#endif
	
	out->set(adir, !adir, bdir, !bdir, aspd, bspd);
	return true;
}

bool DualMotorL298N::coast() {
	if (!out->isValid()) {
		return false;
	}
	
	out->set(1, 0, 1, 0, 0, 0);
	return true;
}
