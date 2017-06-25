#ifndef _TRELLISDRIVER_h
#define _TRELLISDRIVER_h

#include <Adafruit_Trellis.h>

extern Adafruit_Trellis matrix0;
extern Adafruit_TrellisSet trellis;

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN 6

void trellisSetup();
int trellisReadout();

#endif //_TRELLISDRIVER_h

