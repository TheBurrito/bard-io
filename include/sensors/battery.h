#ifndef battery_h_
#define battery_h_

class Battery {
		
public:
	Battery(int bus, int address, int an, float factor, float railV, int bits);
	
	void startRead();
	float getVoltage();
	
	bool isValid();
	
	void setAddress(int address);
	
private:
	int _an;
	
	double _adj;
	
	int _address;
	int _file;
};

#endif //srf08_h_
