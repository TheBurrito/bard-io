#include <output/digitalout.h>

#include <stdlib.h>

int main(int argc, char** argv) {
	DigitalOut out(atoi(argv[1]), atoi(argv[2]));
	return 0;
}
