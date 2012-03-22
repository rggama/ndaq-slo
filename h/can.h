#ifndef CAN_H
#define CAN_H

void initCAN(void);
void rxCAN(void);
void txCAN(unsigned int c);
void send232CAN(void);

#endif

