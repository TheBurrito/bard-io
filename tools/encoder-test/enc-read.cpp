#include <sensors/rotaryencoder.h>

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " eventfile" << endl;
		return 1;
	}
	
	RotaryEncoder re(argv[1]);
	
	while (1) {
		cout << "Reading: " << re.value(10000) << endl;
		
		usleep(500);
	}
	
	return 0;
}
