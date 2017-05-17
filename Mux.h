#ifndef Mux_h
#define Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <audio.h>
#include "effect_gain.h"
#include "debugutils.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Variables
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//extern const int numPiezos;

//available from other file. Maybe not how it should be
//extern AudioPlaySerialflashRaw *playFlashRaw[];
extern AudioEffectGain *EffectGain[];
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void Mux_init(int _S0, int _S1, int _S2, int _MuxA);
int Mux_read(int _input);
void Mux_assign(int _input, int *variable);

#endif
