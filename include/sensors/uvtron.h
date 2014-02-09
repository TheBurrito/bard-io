#ifndef uvtron_h_
#define uvtron_h_

class UVTron {
public:
	UVTron(int addr, unsigned char pin);
	~UVTron();
	
	int read();
	
private:
	int _file;
}

#endif /*uvtron_h_*/
