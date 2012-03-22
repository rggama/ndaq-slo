#ifndef HALFDSPI_H
#define HALFDSPI_H

#include "types.h"


typedef union _BYTE
{
    byte _byte;
    struct
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    };
} BYTE;

#define HSCK			LATBbits.LATB1
#define	T_HSCK			TRISB1
#define SDIO			RB0 //LATBbits.LATB0
#define T_SDIO			TRISB0

#define setInput()		T_SDIO = 1;
#define setOutput()		T_SDIO = 0;
#define toggleCLK(clk)	clk = !clk;
	

void openHalfdSPI(void);
void writeHSPI(BYTE data);
byte readHSPI(void);

#endif
