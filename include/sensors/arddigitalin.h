#ifndef arddigitalin_h_
#define arddigitalin_h_

class ArdDigitalIn {
public:
	ArdDigitalIn(int bus, int address, int pin);
	~ArdDigitalIn();
	
	int read();
	
private:
	int _address;
	int _pin;
	int _file;	
};

#endif /* arddigitalin_h_ */
