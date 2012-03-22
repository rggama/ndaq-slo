#include "csbs.h"
#include "adc.h"
#include "halfdspi.h"
#include "types.h"

void writeADC(byte csb, byte address, byte data)
{
	BYTE temp;

	//Asserting CSB0;
	assertCSB(csb);
	
	//MSB First... 16 bits wide.
	temp._byte = 0x00;
	writeHSPI(temp);		//MSbyte - MSbit = 0, means write... See doc.
	temp._byte = address;
	writeHSPI(temp);		//LSbyte - We have only address bits here.

	temp._byte = data;
	writeHSPI(temp);		//Now it is time to store data.

	//Deasserting CSB0.
	deassertCSB(csb);
}

void resetADC()
{
	writeADC(1, 0x00, 0x3C);
	writeADC(2, 0x00, 0x3C);
	writeADC(3, 0x00, 0x3C);
	writeADC(4, 0x00, 0x3C);

	writeADC(1, 0x00, 0x18);
	writeADC(2, 0x00, 0x18);
	writeADC(3, 0x00, 0x18);
	writeADC(4, 0x00, 0x18);
}
