#include "piezos.h"
#define DEBUG
#include "debugutils.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Read piezo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
const int numPiezos = 4;

typedef enum  {idle=0, rise=1, fall=2} piezoState_t;

typedef struct 
{
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
} PiezoInput;
PiezoInput Piezo[8];

void preReadPiezo(int numPiezo)
{
  Wire.beginTransmission(0x20);
  Wire.write(0x12);
  Wire.write(numPiezo);
  Wire.endTransmission();
}
int PiezoState(int numPiezo)
{
  int piezoRiseThreshold = 50;
  int piezoFallThreshold = 40;
  int p = numPiezo;
  Piezo[p].LastValue = Piezo[p].Value;
  Piezo[p].Value = analogRead(A2);
  Piezo[p].Direction = Piezo[p].Value-Piezo[p].LastValue;
  //state machine
  if(Piezo[p].State == idle && Piezo[p].Value > piezoRiseThreshold)
  {
    Piezo[p].State = rise;
  }
  if(Piezo[p].State == rise && Piezo[p].Direction < 0)
  {
    Piezo[p].State = fall;
    Piezo[p].topValue = Piezo[p].Value;
    Piezo[p].hit = 1;
  }
  if(Piezo[p].State == fall && Piezo[p].Value < piezoFallThreshold)
  {
    Piezo[p].State = idle;
  }
  if(Piezo[p].State == fall && Piezo[p].Direction > 0)
  {
    Piezo[p].State = rise;
  }
  if(Piezo[p].hit == 1)
  {
    Piezo[p].topValue = min(Piezo[p].topValue,1024)-piezoRiseThreshold;
    //max - velocity = velocity range
    Piezo[p].hitGain = (1024 - Piezo[p].velocity) + (Piezo[p].topValue*Piezo[p].velocity)>>10;
    Piezo[p].hitGain<<=10;
    Serial.print("Piezo: ");
    Serial.print(p);
    Serial.print(" - velocity: ");
    Serial.println(Piezo[p].topValue);
    Serial.print(" - gain: ");
    Serial.println(Piezo[p].hitGain);
    Piezo[p].hit=0;
    PiezoSound(p,Piezo[p].hitGain);
  }
  return Piezo[p].Value;
}
uint8_t drainByte;
void PiezoSetSample(int numPiezo, uint16_t numSample)
{
  if(numPiezo > numPiezos) return;
  Piezo[numPiezo].sample = numSample;
  Serial.print("Piezo ");
  Serial.print(numPiezo);
  Serial.print(" - sample ");
  Serial.print(numSample);
  Serial.print(": ");
  Serial.println(serialFlash_Samples[numSample]);
}

void drainPiezos()
{ 
  //select the Input to drain.
  //The outputs of the MCP23017 are directly connected to the bases of the transistors
  //write it to portB
  for(int i=0;i<numPiezos;i++)
  {
     drainByte |= (Piezo[i].State == fall) << i;
     drainByte &= 0xFF ^ ((Piezo[i].State != fall) << i);
  }
  Wire.beginTransmission(0x20);
  Wire.write(0x13);
  Wire.write(drainByte);
  Wire.endTransmission();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Piezosound
//seeks for an idle playFlashRaw and makes it play a sample
//adds one to sampleCountup
//writes "current time" to sampleCounts[8]
//if all are busy
//find the one with the oldest count and replace it with a new one
//
//
//todo:
// - linking pads together, so one can mute the other
//-----------------------------------------------------------------------------------------------------------------------------------------------------------


int PiezoSound(int numPiezo, uint16_t velocity)
{
  static uint32_t sampleCounts[8];
  static uint32_t sampleCountup=0;
  int p = numPiezo;
  char* filename = serialFlash_Samples[Piezo[p].sample];
  for(int i=0;i<8;i++)
  {
    if(!playFlashRaw[i].isPlaying())
    {
      //found an idle play playFlashRaw object, make a sound
      playFlashRaw[i].play(filename);
      gainer[i].gain(velocity);
      sampleCounts[i] = sampleCountup;
      sampleCountup+=1;
      return i;
    }
  }
  //all busy
  //todo: kill the oldest or quitest sound
  uint32_t lowestSampleCount=0xFFFFFFFF;
  int oldestSample=-1;
  for(int i=0;i<8;i++)
  {
    if(lowestSampleCount > sampleCounts[i])
    {
      lowestSampleCount = sampleCounts[i];
      oldestSample = i;
    }
  }
  //found the oldest play playFlashRaw object, make a sound
  playFlashRaw[oldestSample].play(filename);
  gainer[oldestSample].gain(velocity);
  sampleCounts[oldestSample] = sampleCountup;
  sampleCountup+=1;
  return oldestSample;
}
void piezoPreset()
{
  PiezoSetSample(0, 0);
  PiezoSetSample(1, 76);
  PiezoSetSample(2, 37);
  PiezoSetSample(3, 65);
}

