#include "Compiler.h"
#include "csbs.h"
#include "clkd.h"
#include <spi.h>



void writeCLKD(byte address, byte data)
{
	byte ret;

	//Asserting CSB0;
	assertCSB0();
	
	//MSB First... 16 bits wide.
	ret = WriteSPI(0x00);		//MSbyte - MSbit = 0, means write... See doc.
	ret = WriteSPI(address);	//LSbyte - We have only address bits here.

	ret = WriteSPI(data);		//Now it is time to store data.

	//Deasserting CSB0.
	deassertCSB0();
}

void resetCLKD(void)
{
	writeCLKD(0x00, 0x30);
	writeCLKD(0x00, 0x10);
}

byte readCLKD(byte address)
{
	byte ret, data;
	
	//Asserting CSB0.
	assertCSB0();

	WriteSPI(0x80);		//MSbyte - MSbit = 1, means read... See doc.
	WriteSPI(address);	//LSbyte - We have only address bits here.

	//WriteSPI(0xFF);

	//TRISC4 = 1;
	//while (!DataRdySPI());
	
	data = ReadSPI();	//Now it is time to retrieve data.

	//Deasserting CSB0.
	deassertCSB0();

	return data;
}