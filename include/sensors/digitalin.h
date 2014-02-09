#ifndef digitalin_h_
#define digitalin_h_

class GPIO;

class DigitalIn {
public:
	DigitalIn(int gpio);
	~DigitalIn();
	
	int read();
	
private:
	GPIO *_gpio;
};

#endif /* digitalin_h_ */
