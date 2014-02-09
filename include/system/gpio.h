#ifndef gpio_h_
#define gpio_h_

class GPIO {
public:
	GPIO(int gpio);
	GPIO(int gpio, int out);
	GPIO(int gpio, int out, int val);
	
	~GPIO();
	
	void set(int val);
	int get();

private:
	int _file;
	int _gpio;
	
	void init(int gpio, int out, int val);
};

#endif
