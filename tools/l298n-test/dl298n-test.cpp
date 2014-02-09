#include <output/dualmotorl298n.h>

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
	DualMotorL298N out(162, 158, 143, 146, 10, 9);
	
	cout << "Forward" << endl;
	out.drive(5000, 5000);
	sleep(1);
	cout << "Brake" << endl;
	out.brake();
	sleep(1);
	cout << "Left" << endl;
	out.drive(-5000, 5000);
	sleep(1);
	cout << "Brake" << endl;
	out.brake();
	sleep(1);
	cout << "Backward" << endl;
	out.drive(-5000, -5000);
	sleep(1);
	cout << "Brake" << endl;
	out.brake();
	sleep(1);
	cout << "Right" << endl;
	out.drive(5000, -5000);
	sleep(1);
}
