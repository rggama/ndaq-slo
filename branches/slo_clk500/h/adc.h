#ifndef ADC_H
#define ADC_H

#include "types.h"


void writeADC(byte csb, byte address, byte data);
void resetADC(void);

#endif
