#include "Compiler.h"
#include "csbs.h"
#include "dac.h"
#include <spi.h>


void initDAC(word config)
{
	DAC_DATA data;


	//OpenSPI(SPI_FOSC_4, MODE_00, SMPEND); //5 Mbits/s @ 20 MHz - Max 10 Mbits/s @ 40 MHz (PLL?)

	data.wdata = config | CONTROL;

	//Asserting CSB5.
	assertCSB5();

	//MSB First... 16 bits wide.
	WriteSPI(data.msb); //MSbyte
	WriteSPI(data.lsb); //LSbyte

	//Deasserting CSB5.
	deassertCSB5();

	//Asserting CSB6.
	assertCSB6();

	//MSB First... 16 bits wide.
	WriteSPI(data.msb); //MSbyte
	WriteSPI(data.lsb); //LSbyte

	//Deasserting CSB6.
	deassertCSB6();
}

void writeDAC(byte csb, byte channel, DAC_DATA data)
{
	word wchannel;

	wchannel = (word)channel;
	data.wdata = ((data.wdata & 0x0FFF) | ((wchannel << 12) & 0x7000)); //moving bits...

	//Asserting CSB5.
	assertCSB(csb);
	
	//MSB First... 16 bits wide.
	WriteSPI(data.msb); //MSbyte
	WriteSPI(data.lsb); //LSbyte

	//Deasserting CSB5.
	deassertCSB(csb);
}
