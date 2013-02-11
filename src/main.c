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
	deassertCSB1();
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

	//Configuring AD9510 PLL Loop.
	//In Fixed Divider mode (for N feedback divider), we have:
	//Fvco = Fref * N/R
	//Thus, N/R = 2 for Fvco = 125 MHz and Fref = 62.5 MHz.
	//Where N is the feedback divider and R is the reference divider.
	//Let N = 2 and R = 1. See below.
	
	//R divider (Reference divider)
	//R divider is set to '1'. 
	writeCLKD(0x0C, 0x01);
	writeCLKD(0x0B, 0x00);

	//N divider (Vco feedback divider)
	//N divider: N(P, A, B).
	//N = P*B+A.
	//P is a prescaler (3 bits).
	//A and B are counters, 6 and 3 bits respectively.
	//Two modes are possible: FD (fixedd divider) and DM (dual modulus).
	//In FD mode, A is not used.
	
	//Set P prescaler to 2 and set B counter to 1 (bypass). Also set PLL to Normal Operation.
	writeCLKD(0x0A, 0x44);	

	writeCLKD(0x07, 0x04);	//Enable Loss of Reference (LOR) function.

	writeCLKD(0x08, 0x0F);	//Set Normal Operation mode to CP and STATUS Pin to 'Loss of Lock (active high)'.
	//writeCLKD(0x08, 0x0D);	//Set Pump-up mode to CP and STATUS Pin to 'Loss of Lock (active high)'.
	//writeCLKD(0x08, 0x37);	//Set Normal Operation mode to CP and STATUS Pin to 'Loss of Lock or Loss of Ref (active high)'.
	//writeCLKD(0x08, 0x2B);	//Set Normal Operation to CP and STATUS Pin to 'Loss of Ref (active high)'.
	//writeCLKD(0x08, 0x35);	//Set Pump-up mode to CP and STATUS Pin to 'Loss of Lock or Loss of Ref (active high)'.
	
	//writeCLKD(0x09, 0x40);	//Set CP current to 3.0 mA.
	writeCLKD(0x09, 0x00);	//Set CP current to 0.6 mA.
	
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
	writeADC(1, 0x08, 0x00);	//0x00: Normal op. - 0x01: Full Power Down.
	writeADC(1, 0x14, 0xC1);	//LVDS and two's comlement.
	writeADC(1, 0x0D, 0x00);	//Self Test - 0x00: Normal op. - 0x07: one/zero word toggle.
	writeADC(1, 0xFF, 0x01);	//Master Register latch enable - self resetable.

	//for ADC34	
	writeADC(2, 0x08, 0x00);	
	writeADC(2, 0x14, 0xC1);	
	writeADC(2, 0xFF, 0x01);	 
	
	//for ADC56
	writeADC(4, 0x08, 0x00);	
	writeADC(4, 0x14, 0xC1);	
	writeADC(4, 0xFF, 0x01);	

	//for ADC78
	writeADC(3, 0x08, 0x00); //0x01	
	writeADC(3, 0x14, 0xC1);	
	writeADC(3, 0xFF, 0x01);	
	

	data.wdata = 512; //~313mV
	writeDAC(5, 0, data);
	writeDAC(5, 1, data);
	writeDAC(5, 2, data);
	writeDAC(5, 3, data);
	writeDAC(5, 4, data);
	writeDAC(5, 5, data);
	writeDAC(5, 6, data);
	writeDAC(5, 7, data);

	for(;;)
	{
		//test = readCLKD(0x45);
		//writeCLKD(0x5A, 0x01);

		//bdata._byte = 0xAA;
		//writeHSPI(bdata);

		for(i=0;i<10000;i++);

		
		//data.wdata = sweep;	
		//writeDAC(5, 0, data);
		//writeDAC(6, 0, data);
		//sweep++;
		//if (sweep>4095) sweep = 0;
		

		//rxCAN();
	}
	

	//for(;;);	

}

