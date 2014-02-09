#include <sensors/arddigitalin.h>

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {
	ArdDigitalIn in(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	int v = in.read();
	cout << v << endl;
	return v;
}
