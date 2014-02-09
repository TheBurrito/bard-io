#ifndef dualmotorl298n_h_
#define dualmotorl298n_h_

class L298N;

class DualMotorL298N {

public:
	DualMotorL298N(int in1, int in2, int in3, int in4, int ena, int enb);
	~DualMotorL298N();
	
	bool brake();
	bool drive(int a, int b);
	bool coast();

private:
	L298N* out;
};

#endif /* dualmotorl298n_h_ */
