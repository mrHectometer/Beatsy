#ifndef FlashStorage_h
#define FlashStorage_h

#include <SerialFlash.h>
extern char serialFlash_Samples[256][20];
extern int serialFlash_nSamples;
int serialFlash_Samples_List();
int setupFlash(int FlashChipSelect);
#endif
