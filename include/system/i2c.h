
#ifndef i2c_h_
#define i2c_h_

int set_slave_addr(int file, int address, int force);
int i2c_open_bus(int bus);

#endif /*i2c_h_*/
