#ifndef piezos_h
#define piezos_h

#include <Arduino.h>
#include <Wire.h>
#include <audio.h>
#include "flashstorage.h"
#include "effect_gain.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Variables
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
extern const int numPiezos;

//available from other file. Maybe not how it should be
extern AudioPlaySerialflashRaw *playFlashRaw[];
extern AudioEffectGain *EffectGain[];
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void preReadPiezo(int numPiezo);
void PiezoSetSample(int numPiezo, uint16_t numSample);
int PiezoState(int numPiezo);
void drainPiezos();
int PiezoSound(int numPiezo, uint16_t velocity);
void piezoPreset();

#endif
