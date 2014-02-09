#ifndef srf08_h_
#define srf08_h_

class SRF08 {
public:
	enum Units { IN = 0x50, CM = 0x51, uS = 0x52 };
		
public:
	SRF08(int bus, int address, SRF08::Units units);
	
	void startRange();
	int getRange();
	int getVersion();
	int getLight();
	
	bool isValid();
	
	bool isReady();
	
	void setAddress(int address);
	void setUnits(Units units);
	
private:
	Units _units;
	int _address;
	int _file;
};

#endif //srf08_h_
