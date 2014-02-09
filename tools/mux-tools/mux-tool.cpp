#include <system/usermux.h>

#include <cstdlib>
#include <iostream>

using namespace std;

void usage(char* name) {
	cout << "Usage: " << name << " address [mode input_enable pu_en pu_up]\n" << endl;
	cout << "\taddress: Address of pad config. Uses half-word addresses" << endl;
	cout << "\tmode: Mux mode for the pin, 0-7" << endl;
	cout << "\tinput_enable: 1 to enable using pin as input, 0 otherwise" << endl;
	cout << "\tpu_en: 1 to enable the pull up/down, 0 to disable" << endl;
	cout << "\tpu_up: 1 to use pull up, 0 for pull down" << endl;
}

int main(int argc, char** argv) {

	MuxConfig mux;
	
	if (argc < 7) {
		if (argc < 2) {
			usage(argv[0]);
			exit(1);
		}
		
		mux.address = strtoul(argv[1], 0, 0);
		
		if (argc > 2) {
			cout << "Setting mux value for address 0x" << hex << mux.address << endl;
			
			mux.mode = atoi(argv[2]);
			mux.input_enable = atoi(argv[3]);
			mux.pullupdown_enable = atoi(argv[4]);
			mux.pullupdown_up = atoi(argv[5]);
			
			cout << "Writing register value: 0x" << hex << muxtoreg(&mux) << endl;
			
			if (setmux(&mux)) {
				cout << "\tError setting mux configuration" << endl;
			} else {
				cout << "\tMux set successfully." << endl;
			}
		} else {
			if (getmux(&mux)) {
				cerr << "Error reading mux configuration" << endl;
			} else {
				cout << "Mux config for address 0x" << hex << mux.address << endl;
				cout << "\tMode: " << dec << mux.mode << endl;
				
				cout << "\tInput: ";
				if (mux.input_enable) {
					cout << "enabled";
				} else {
					cout << "disabled";
				}
				cout << endl;
				
				cout << "\tPull Up/Down: ";
				if (mux.pullupdown_enable) {
					if (mux.pullupdown_up) {
						cout << "up";
					} else {
						cout << "down";
					}
					cout << endl;
				} else {
					cout << "disabled";
				}
				cout << endl;
			}
		}
	}
}
