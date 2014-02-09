#include <sensors/srf08.h>

#include <iostream>

#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	int numSonar = argc - 1;
	
	if (numSonar < 1) {
		cout << "Usage: " << argv[0] << " Address1 [Address2 [Address3 [...] ] ]" << endl;
		exit(1);
	}
	
	SRF08** sonars = (SRF08**)malloc(numSonar * sizeof(SRF08*));
	
	for (int i = 0; i < numSonar; ++i) {
		cout << "Attaching to SRF08 at address " << argv[i + 1] << endl;
		sonars[i] = new SRF08(2, atoi(argv[i + 1]), SRF08::CM);
		if (!sonars[i]->isValid()) {
			cout << "Error opening I2C bus. Exiting." <<endl;
			exit(1);
		}
	}
	
	int curSonar = 0;
	
	sonars[curSonar]->startRange();
	
	while (1) {
		if (sonars[curSonar]->isReady()) {
			cout << " " << sonars[curSonar]->getRange() << " cm ";
			curSonar++;
			if (curSonar == numSonar) {
				curSonar = 0;
				cout << endl;
			}
		
			sonars[curSonar]->startRange();
		}
		
		sleep(0);
	}
}
