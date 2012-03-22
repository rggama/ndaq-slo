#include "Compiler.h"
#include "can.h"
#include ".\can\can18xx8.h"
#include <usart.h>


void initCAN(void)
{
	CANInitialize(
					1, /*SJW*/ 
					5, /*BRP*/
					7, /*PHSEG1*/
					6, /*PHSEG2*/
					2, /*PROPSEG*/
					CAN_CONFIG_ALL_MSG
	);

	//FOSC = 20 MHz (No PLL).
	//TQ = (2*BRP)/FOSC = 0,5uS.
	//NBT = 1*TQ + 7*TQ + 6*TQ + 2*TQ = 16*TQ = 8uS.
    //1/NBT = 125000. 
    //125Kbps @ 20 MHz.

	//Setting the CAN Transceiver to "High Speed" thru the slope control.
	TRISB4 = 0;
	RB4 = 0;

	//1762 made 125Kbps @ 20 MHz for BRP = 5
	//1331 made 250Kbps @ 20 MHz for BRP = 5
	//1111 made 500Kbps @ 20 MHz for BRP = 5 - WOW!
	//1432 made 1Mbps @ 20 MHz for BRP = 1 with ERRORS! 
	//1621 made 1Mpbs @ 20 MHz for BRP = 1 with less ERRORS!
}

//Echoing CAN message to RS232 (CAN -> RS232)
void rxCAN(void)
{
	unsigned long id;
	BYTE data[8];
	BYTE lenght;
	enum CAN_RX_MSG_FLAGS mflags;
	BYTE i;

	if (CANIsRxReady())
	{
		CANReceiveMessage(&id, data, &lenght, &mflags);

		//Echoing message to the RS232
		for(i=0;i<8;i++)
		{
			while(BusyUSART());
			putcUSART(data[i]);
		}
		
		/*
		if (id == 0x01)
			txCAN(data[0]); //loopback
		*/

		//reseting buffer
		for(i=0;i<8;i++)
		{
			data[i] = 0x00; //null char
		}
	}
}

void txCAN(unsigned int c)
{
	unsigned long id;
	BYTE data[8];
	BYTE lenght;
	BYTE i;
	
	//reseting buffer
	for(i=0;i<8;i++)
	{
		data[i] = 0x00; //null char
	}

	data[0] = c;

	if (CANIsTxReady())
	{
		CANSendMessage(	0x02, 
						data, 
						0x08,
						CAN_TX_PRIORITY_0 &
						CAN_TX_STD_FRAME &
						CAN_TX_NO_RTR_FRAME);
	}
}


//Echoing RS232 message to CAN (RS232 -> CAN)
#pragma interruptlow send232CAN /*save=section("LABEL")*/
void send232CAN(void)
{
	txCAN(getcUSART());
}
