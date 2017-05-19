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
extern AudioPlaySerialflashRaw playFlashRaw[];
extern AudioEffectGain gainer[];
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void preReadPiezo(int numPiezo);
void PiezoSetSample(int numPiezo, uint16_t numSample);
int PiezoState(int numPiezo);
void drainPiezos();
int PiezoSound(int numPiezo, uint16_t velocity);
void piezoPreset();
/*
class piezo
{
  public:
  preRead();
  setSample(uint16_t numSample);
  read();
  drain();
  sound(uint16_t velocity);
  private:
  int16_t Value;
  int16_t topValue;
  int16_t LastValue;
  int16_t Direction;
  int16_t timeOut;//(probably) needed after draining to avoid bouncing
  int16_t sample;
  int16_t velocity = 256;//0-512
  int16_t sampleGain;
  int16_t hitGain;
  bool hit;
  piezoState_t State;
};*/
#endif
