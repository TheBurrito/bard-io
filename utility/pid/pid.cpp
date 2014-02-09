#include <utility/pid.h>

double timeSecs() {
	struct timeval t;
	gettimeofday(&t, 0);
	double secs = t.tv_sec + (t.tv_usec / 1000000.0);
}

void initPID(PID& pid, double p, double i, double d) {
	pid.p = p;
	pid.i = i;
	pid.d = d;
	pid._e = 0;
	pid._s = 0;
	pid.s_max = 0;
}

void initPID(PID& pid, double p, double i, double d, double s_max) {
	initPID(pid, p, i, d);
	pid.s_max = s_max;
}

void resetPID(PID& pid) {
	pid._e = 0;
	pid._s = 0;
}

double calcPID(PID& pid, const double error, const double dt) {
	pid._s += error * dt;
	
	double p = pid.p * error;
	double i = pid.i * pid._s;
	double d = pid.d * (pid._e - error) / dt;
	
	if (pid.s_max && pid.i) {
		double max = pid.s_max - p;
		if (i  > max ) {
			pid._s = max / pid.i;
			i = max;
		} else if (i < -max) {
			pid._s = -max / pid.i;
			i = max;
		}
	}
	
	double ret = p + i - d;
	pid._e = error;
	
	return ret;
}
