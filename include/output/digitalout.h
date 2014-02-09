#ifndef gpio_h_
#define gpio_h_

class GPIO;

class DigitalOut {
public:
	DigitalOut(int gpio, int val);
	~DigitalOut();
	
	void set(int val);
	
private:
	GPIO *_gpio;
};

#endif /*gpio_h_*/
