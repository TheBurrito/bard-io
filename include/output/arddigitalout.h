#ifndef arddigitalout_h_
#define arddigitalout_h_

class ArdDigitalOut {
public:
	ArdDigitalOut(int bus, int address, int val);
	~ArdDigitalOut();
	
	void set(int val);
	
private:
	int _file;
	int _address;
};

#endif /* arddigitalout_h_ */
