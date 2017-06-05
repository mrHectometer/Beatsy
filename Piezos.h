#ifndef piezos_h
#define piezos_h
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Includes
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include <audio.h>
#include <debugtools.h>
#include "flashstorage.h"
#include "effect_gain.h"
#include "flashStorage.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Variables
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
const int numPiezos = 4;

//available from other file. Maybe not how it should be
extern AudioPlaySerialflashRaw playFlashRaw[];
extern AudioEffectGain gainer[];
typedef enum  {idle=0, rise=1, fall=2} piezoState_t;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void drainPiezos();
void setupPiezos();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Main piezo class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class piezoInput
{
  public:
  int16_t sampleGain = 1024;
  void setSample(uint16_t numSample);
  void preRead();
  int doState();
  void playSample(uint16_t velocity);
  void setPhysicalInput(int i){physicalInput=i;}
  piezoState_t getState() {return State;}
  void incrementSample();
  void decrementSample();
  int16_t velocity = 256;//0-1024
  private:
  int16_t Value;
  int16_t topValue;
  int16_t LastValue;
  int16_t Direction;
  int16_t timeOut;//(probably) needed after draining to avoid bouncing
  int16_t sample;
  int physicalInput;
  piezoState_t State;
};
extern piezoInput Piezo[];
#endif
