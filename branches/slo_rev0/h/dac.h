#ifndef DAC_H
#define DAC_H

#include "types.h"


typedef union _DAC_DATA
{
	word wdata;

	struct
	{
		byte lsb;
		byte msb;
	};

} DAC_DATA;


#define GR0_VDD		0x0001
#define	GR1_VDD		0x0002
#define GR0_BUF		0x0004
#define GR1_BUF		0x0008
#define GR0_GAIN	0x0010
#define	GR1_GAIN	0x0020
#define CONTROL		0x8000
#define	LDAC		0xA000
#define POWER_DOWN	0xC000
//#define RESET 

void initDAC(word config);
void writeDAC(byte csb, byte channel, DAC_DATA data);

#endif
