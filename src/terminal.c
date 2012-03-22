#include "Compiler.h"
#include "terminal.h"
#include <usart.h>

void initTERM(void)
{
	OpenUSART(	USART_TX_INT_OFF &
				USART_RX_INT_ON &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_HIGH,
				10L
	);	

	RCONbits.IPEN = 1;					
	GIEH = 1;							//High Interrupts ON.
	GIEL = 1;							//Low Interrupts ON.
}

void loopUSART(void)
{
	while(!DataRdyUSART());
	putcUSART(getcUSART());
}

/*
#pragma interruptlow loopUSARTi 
void loopUSARTi(void)
{
	putcUSART(getcUSART());
}
*/