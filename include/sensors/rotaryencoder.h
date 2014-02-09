#ifndef rotary_encoder_h_
#define rotary_encoder_h_

struct input_event;

class RotaryEncoder {
public:

	RotaryEncoder(const char* dev);
	~RotaryEncoder();
	
	int value(int timeout_uS);
	struct input_event* event();
	
private:
	int _file;
	int _val;
};

#endif /*rotary_encoder_h_*/
