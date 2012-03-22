#include "Compiler.h"	//Compiler definitions
#include "terminal.h"	//UART controller (proto only)
#include "can.h"		//CAN controller
#include "fulldspi.h"	//Full Duplex SPI controller (peripheral)
#include "halfdspi.h"	//Half Duples SPI controller (software)
#include "csbs.h"		//Chip select handler
#include "dac.h"		//DAC configuration routines
#include "clkd.h"		//Clock Distributor configuration routines
#include "adc.h"		//ADC configuration routines


extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x00020
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

/*
#pragma code high_vector=0x808
void hi_interrupt(void)
{
  _asm goto loopUSARTi _endasm
}
#pragma code
*/

/*
#pragma code low_vector=0x018
void lo_interrupt(void)
{
  _asm goto send232CAN _endasm
}
#pragma code
*/

void main(void)
{
	unsigned int i,sweep=0;
	DAC_DATA data;
	byte test;
	BYTE bdata;

	deassertCSB0();
	deassertCSB2();
	deassertCSB3();
	deassertCSB4();
	deassertCSB5();
	deassertCSB6();
	
	openFulldSPI();
	openHalfdSPI();

	//initTERM();
	initCAN();
	initDAC(0);

	
	resetCLKD();
	resetADC();
	
	//writeCLKD(0x08, 0x01);	//Set Pump-up mode to CP.
	//writeCLKD(0x08, 0x03);	//Set Normal Operation mode to CP.
	//writeCLKD(0x09, 0x40);	//Set CP current to 3.0 mA.
	//writeCLKD(0x0A, 0x00);	//Set PLL to Normal Operation.
	
	writeCLKD(0x45, 0x02);	//Set CLK2 as Distribution input, power down CLK1 input. See doc.

	writeCLKD(0x42, 0x02);	//Enable OUT6
	writeCLKD(0x43, 0x02);	//Enable OUT7

	writeCLKD(0x4B, 0xC0);	//(OUT1) Set 'Ignore Chip-Level Sync Signal' and 'Bypass and Power-Down Divider Logic'. See doc.

	writeCLKD(0x51, 0xC0);	//(OUT4 - ADC78) Set 'Ignore Chip-Level Sync Signal' and 'Bypass and Power-Down Divider Logic'. See doc.
	writeCLKD(0x53, 0xC0);	//(OUT5 - ADC56) Set 'Ignore Chip-Level Sync Signal' and 'Bypass and Power-Down Divider Logic'. See doc.
	writeCLKD(0x55, 0xC0);	//(OUT6 - ADC34) Set 'Ignore Chip-Level Sync Signal' and 'Bypass and Power-Down Divider Logic'. See doc.
	writeCLKD(0x57, 0xC0);	//(OUT7 - ADC12) Set 'Ignore Chip-Level Sync Signal' and 'Bypass and Power-Down Divider Logic'. See doc.

	//writeCLKD(0x57, 0x40);	//(OUT7 - ADC12) Divider Logic Enabled - Dividing by 2 (Default) - Phase 0.
	//writeCLKD(0x55, 0x41);	//(OUT6 - ADC34) Divider Logic Enabled - Dividing by 2 (Default) - Phase 1.

	//test = readCLKD(0x45);

	writeCLKD(0x5A, 0x01);	//Update Registers with SPI Buffers Content.
	
	/*********************************/

	//for ADC12
	writeADC(2, 0x08, 0x01);	//0x00: Normal op. - 0x01: Full Power Down.
	writeADC(2, 0x14, 0xC1);	//LVDS and two's comlement.
	writeADC(2, 0x0D, 0x00);	//Self Test - 0x00: Normal op. - 0x07: one/zero word toggle.
	writeADC(2, 0xFF, 0x01);	//Master Register latch enable - self resetable.

	//for ADC34	
	writeADC(3, 0x08, 0x01);	
	writeADC(3, 0x14, 0xC1);	
	writeADC(3, 0xFF, 0x01);	 
	
	//for ADC56
	writeADC(4, 0x08, 0x01);	
	writeADC(4, 0x14, 0xC1);	
	writeADC(4, 0xFF, 0x01);	

	//for ADC78
	writeADC(5, 0x08, 0x01); //0x01	
	writeADC(5, 0x14, 0xC1);	
	writeADC(5, 0xFF, 0x01);	
	

	data.wdata = 512; //~313mV
	writeDAC(5, 0, data);
	writeDAC(5, 1, data);
	writeDAC(5, 2, data);
	writeDAC(5, 3, data);
	writeDAC(5, 4, data);
	writeDAC(5, 5, data);
	writeDAC(5, 6, data);
	writeDAC(5, 7, data);

	/*
	for(;;)
	{
		//test = readCLKD(0x45);
		//writeCLKD(0x5A, 0x01);

		//bdata._byte = 0xAA;
		//writeHSPI(bdata);

		//for(i=0;i<10000;i++);

		
		data.wdata = sweep;	
		writeDAC(5, 0, data);
		writeDAC(6, 0, data);
		sweep++;
		if (sweep>4095) sweep = 0;
		

		//rxCAN();
	}
	*/

	for(;;);	

}

