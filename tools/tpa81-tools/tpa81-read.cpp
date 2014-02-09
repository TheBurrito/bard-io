#include <sensors/tpa81.h>

#include <iostream>

#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	uint8_t *temps, *cur;
	uint8_t amb, diff;
	
	TPA81 t(2, 0x68, 1);
	
	while (1) {
		t.update();
		
		amb = t.getAmbient();
		cur = t.getTemps();
		
		if (cur) {
		#ifdef DEBUG
			cout << "Check for diff..." << endl;
		#endif
		
		diff = 0;
		if (!temps) {
			diff = 1;
		} else {
			for (int i = 0; i < 8; ++i) {
				if (cur[i] != temps[i]) {
					diff = 1;
					break;
				}
			}
		}
		
		#ifdef DEBUG
			cout << "Readings:" << endl;
		#endif
		
		if (diff) {
			cout << ((int)amb) << " : ";
			for (int i = 0; i < 8; ++i) {
				cout << ((int)cur[i]) << " ";
			}
			cout << endl;
		}
		
		if (temps) {
			free(temps);
		}
		
		temps = cur;
		}
		
		usleep(10000);
	}
	
	return 0;
}
