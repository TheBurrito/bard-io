#ifndef _l298n_h
#define _l298n_h

class GPIO;

class L298N {
public:
	/*
		Initializes the selected pins as output to the L298N.
		in1 - in4 are the gpio pin number to use. Due to the vast differences
			in omap systems, these must be muxed as needed ahead of time.
		ena, enb are the pwm number to use. Most OMAP systems have 4 PWMs, with
			the beagleboard having 3 available on the expansion header.
			Valid PWMs are 8, 9, 10, 11. This class uses a modified omap3-pwm
			kernel-space driver to set the pwm duty cycles.
	*/
	L298N(int in1, int in2, int in3, int in4, int ena, int enb);
	
	~L298N();
	
	/*
	set takes the values passed in and sets the appropriate output.
	in1 - in4 are just on/off values. 0 for off, anything else for on.
	ena, enb are duty cycles with a value of hundredths of a percent.
		IE: for 25% duty cycle, set ena to 2500
	*/
	void set(int in1, int in2, int in3, int in4, int ena, int enb);
	
	bool isValid();
	
private:
	GPIO *_in1, *_in2, *_in3, *_in4;
	int _fda, _fdb;
	bool _valid;
};

#endif /*_l298n_h*/
