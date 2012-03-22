#include "Compiler.h"
#include "halfdspi.h"

//REMOVE WHEN POSSIBLE!
#include "csbs.h"

void openHalfdSPI(void)
{
	setInput();	
	T_HSCK	= 0;
	HSCK	= 0;
}

void writeHSPI(BYTE data)
{
	setOutput();
	
	//Serial engine: MSb First
	HSCK = 0;
	SDIO = data.b7;
	HSCK = 1;

	SDIO = data.b7;

	HSCK = 0;
	SDIO = data.b6;
	HSCK = 1;

	SDIO = data.b6;

	HSCK = 0;
	SDIO = data.b5;
	HSCK = 1;

	SDIO = data.b5;

	HSCK = 0;
	SDIO = data.b4;
	HSCK = 1;

	SDIO = data.b4;

	HSCK = 0;
	SDIO = data.b3;
	HSCK = 1;

	SDIO = data.b3;
	
	HSCK = 0;
	SDIO = data.b2;
	HSCK = 1;

	SDIO = data.b2;

	HSCK = 0;
	SDIO = data.b1;
	HSCK = 1;

	SDIO = data.b1;

	HSCK = 0;
	SDIO = data.b0;
	HSCK = 1;

	SDIO = data.b0;

	HSCK = 0;
	//end of Serial Engine
	

	setInput();
}

byte readHSPI(void)
{
	BYTE data;


	setInput();

	//Serial Engine: MSb first
	HSCK = 0;
	toggleCLK(HSCK);
	data.b7 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b6 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b5 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b4 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b3 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b2 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b1 = SDIO;

	toggleCLK(HSCK);
	toggleCLK(HSCK);
	data.b0 = SDIO;

	HSCK = 0;
	//end of Serial Input Engine

	return data._byte;
}
