#ifndef tpa81_h_
#define tpa81_h_

#include <stdint.h>

class TPA81 {
public:
	TPA81(int bus, int address, uint8_t reverse);
	
	bool isValid();
	
	void update();
	uint8_t getAmbient();
	uint8_t* getTemps();
	
private:
	uint8_t _ambient;
	uint8_t _temps[8];
	uint8_t _reverse;
	
	int _address;
	int _file;
};

#endif
