#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <WProgram.h>

#ifdef DEBUG
#define DEBUG_PRINT(arg)    \
    Serial.print(millis());     \
    Serial.print(": ");    \
    Serial.print(__PRETTY_FUNCTION__); \
    Serial.print(' ');      \
    Serial.print(__LINE__);     \
    Serial.print(' ');      \
    Serial.print(#arg);    \
    Serial.print(" = ");    \
    Serial.println(arg);
    
#else
#define DEBUG_PRINT(arg)
#endif

#endif
