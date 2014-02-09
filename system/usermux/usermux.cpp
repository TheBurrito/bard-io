#include <system/usermux.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

unsigned short muxtoreg(MuxConfig* mux) {

	short						writeval = mux->mode & 7;
	if (mux->input_enable) 		writeval |= 1 << 8;
	if (mux->pullupdown_enable)	writeval |= 1 << 3;
	if (mux->pullupdown_up) 	writeval |= 1 << 4;
	
	return writeval;
}

int setmux(MuxConfig* mux) {
	int fd;
    void *map_base, *virt_addr; 
	unsigned short writeval;
	
	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		return -1;
	}
	
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mux->address & ~MAP_MASK);

    if(map_base == (void *) -1) return -1;
    
	virt_addr = (char*)map_base + (mux->address & MAP_MASK);
	
	writeval = muxtoreg(mux);
		
	*((unsigned short *) virt_addr) = writeval;
	
	if (close(fd)) return -1;
	
	return 0;
}

int getmux(MuxConfig* mux) {
	int fd;
    void *map_base, *virt_addr; 
	unsigned short readval;
	
	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		return -1;
	}
	
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mux->address & ~MAP_MASK);

    if(map_base == (void *) -1) return -1;
	
	virt_addr = (char*)map_base + (mux->address & MAP_MASK);
		
	readval = *((unsigned short *) virt_addr);
	
	mux->mode 				= readval &   0x7;
	mux->pullupdown_enable 	= (readval &   0x8) != 0;
	mux->pullupdown_up 		= (readval &  0x10) != 0;
	mux->input_enable 		= (readval & 0x100) != 0;
	
	if (close(fd)) return -1;
	
	return 0;
}
