#ifndef usermux_h_
#define usermux_h_

/*
These defines are based on the GPIO pins available on the Beagleboard C4 breakout header.
Use these when setting up a mux config to call with setmux and getmux
*/
/*MMC2_CLK0*/
#define GPIO_PIN_130 0x48002158 
/*MMC2_CMD*/
#define GPIO_PIN_131 0x4800215A 
/*MMC2_DAT0*/
#define GPIO_PIN_132 0x4800215C 
/*MMC2_DAT1*/
#define GPIO_PIN_133 0x4800215E 
/*MMC2_DAT2*/
#define GPIO_PIN_134 0x48002160 
/*MMC2_DAT3*/
#define GPIO_PIN_135 0x48002162 
/*MMC2_DAT4*/
#define GPIO_PIN_136 0x48002164 
/*MMC2_DAT5*/
#define GPIO_PIN_137 0x48002166 
/*MMC2_DAT6*/
#define GPIO_PIN_138 0x48002168 
/*MMC2_DAT7*/
#define GPIO_PIN_139 0x4800216A 
/*MCBSP3_FSX*/
#define GPIO_PIN_143 0x48002172 
/*UART2_CTS*/
#define GPIO_PIN_144 0x48002174 
/*UART2_RTS*/
#define GPIO_PIN_145 0x48002176 
/*UART2_TX*/
#define GPIO_PIN_146 0x48002178 
/*MCBSP1_CLKR*/
#define GPIO_PIN_156 0x4800218C 
/*MCBSP1_FSR*/
#define GPIO_PIN_157 0x4800218E 
/*MCBSP1_DX*/
#define GPIO_PIN_158 0x48002190 
/*MCBSP1_DR*/
#define GPIO_PIN_159 0x48002192 
/*MCBSP1_FSX*/
#define GPIO_PIN_161 0x48002196 
/*MCBSP1_CLKX*/
#define GPIO_PIN_162 0x48002198 
/*I2C2_SCL*/
#define GPIO_PIN_168 0x480021BE 
/*I2C2_SDA*/
#define GPIO_PIN_183 0x480021C0 

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long pinaddr_t;

typedef struct {
	pinaddr_t address;
	int mode;
	int input_enable;
	int pullupdown_enable;
	int pullupdown_up;
} MuxConfig;

int setmux(MuxConfig* mux);
int getmux(MuxConfig* mux);
unsigned short muxtoreg(MuxConfig* mux);

#ifdef __cplusplus
}
#endif
#endif //usermux_h_
