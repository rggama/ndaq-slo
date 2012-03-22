#include "csbs.h"

void assertCSB(byte csb)
{
	switch(csb)
	{
		case 0: assertCSB0(); break;
		case 1: assertCSB1(); break;
		case 2: assertCSB2(); break;
		case 3: assertCSB3(); break;
		case 4: assertCSB4(); break;
		case 5: assertCSB5(); break;
		case 6: assertCSB6(); break;
		default: break;
	}
}

void deassertCSB(byte csb)
{
	switch(csb)
	{
		case 0: deassertCSB0(); break;
		case 1: deassertCSB1(); break;
		case 2: deassertCSB2(); break;
		case 3: deassertCSB3(); break;
		case 4: deassertCSB4(); break;
		case 5: deassertCSB5(); break;
		case 6: deassertCSB6(); break;
		default: break;
	}
}
