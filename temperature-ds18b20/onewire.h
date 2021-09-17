#ifndef __onewire_H__
#define __onewire_H__

unsigned char  onewire_init(void);
unsigned char onewire_receivebyte(void);
void onewire_sendbyte(unsigned char byte);
void onewire_sentbit(unsigned char BIT);
unsigned char onewire_receivebit(void);

#endif