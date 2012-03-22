#include "Compiler.h"
#include "fulldspi.h"
#include <spi.h>

/*
** SPI Modes:
**
** MODE 0,0 (should work)
**   CKP: 0
**   CKE: 1
**
** MODE 1,0 (should work)
**   CKP: 1
**   CKE: 1
**
** MODE 1,1 
**   CKP: 1
**   CKE: 0
**
** MODE 0,1 (default)
**   CKP: 0
**   CKE: 0
**
*/

void  openFulldSPI(void)
{
	OpenSPI(SPI_FOSC_4, MODE_00, SMPEND); //5 Mbits/s @ 20 MHz - Max 10 Mbits/s @ 40 MHz (PLL?)
}
