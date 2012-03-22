#ifndef CSBS_H
#define CSBS_H

#include "Compiler.h"
#include "types.h"


#define CSB0			LATA0
#define T_CSB0			TRISA0
#define CSB1			LATA1
#define T_CSB1			TRISA1
#define CSB2			LATA2
#define T_CSB2			TRISA2
#define CSB3			LATA3
#define T_CSB3			TRISA3
#define CSB4			LATA4
#define T_CSB4			TRISA4
#define CSB5			LATA5
#define T_CSB5			TRISA5
#define CSB6			LATC7
#define T_CSB6			TRISC7

#define assertCSB0()	CSB0 = 0; T_CSB0 = 0;
#define deassertCSB0()	CSB0 = 1; T_CSB0 = 0;
#define assertCSB1()	CSB1 = 0; T_CSB1 = 0;
#define deassertCSB1()	CSB1 = 1; T_CSB1 = 0;
#define assertCSB2()	CSB2 = 0; T_CSB2 = 0; 
#define deassertCSB2()	CSB2 = 1; T_CSB2 = 0; 
#define assertCSB3()	CSB3 = 0; T_CSB3 = 0; 
#define deassertCSB3()	CSB3 = 1; T_CSB3 = 0; 
#define assertCSB4()	CSB4 = 0; T_CSB4 = 0; 
#define deassertCSB4()	CSB4 = 1; T_CSB4 = 0; 
#define assertCSB5()	CSB5 = 0; T_CSB5 = 0; 
#define deassertCSB5()	CSB5 = 1; T_CSB5 = 0; 
#define assertCSB6()	CSB6 = 0; T_CSB6 = 0; 
#define deassertCSB6()	CSB6 = 1; T_CSB6 = 0;

void assertCSB(byte csb);
void deassertCSB(byte csb);

#endif