#ifndef CLKD_H
#define CLKD_H

#include "types.h"


void writeCLKD(byte address, byte data);
void resetCLKD(void);
byte readCLKD(byte address);

#endif
