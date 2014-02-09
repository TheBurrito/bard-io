#ifndef pid_h_
#define pid_h_

#include <sys/time.h>

typedef struct {
	double p; /* Proportional term factor */
	double i; /* Integral term factor */
	double d; /* Derivative term factor */
	
	double s_max; /* Maximum error cap, 0 for no cap */
	
	double _s;
	double _e;
} PID;

inline double timeSecs();

void initPID(PID& pid, double p, double i, double d);
void initPID(PID& pid, double p, double i, double d, double s_max);

double calcPID(PID& pid, const double error, const double dt);

void resetPID(PID& pid);

#endif /* pid_h_ */
