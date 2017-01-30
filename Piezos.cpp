#include "piezos.h"
#define DEBUG
#include "debugutils.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Read piezo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int PiezoCurrentValue[8];
int PiezoLastValue[8];
int PiezoDirection[8];
int numPiezos = 4;

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
   int16_t gain;
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
  int piezoRiseThreshold = 30;
  int piezoFallThreshold = 20;
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
    
    Piezo[p].topValue = min(Piezo[p].topValue,1024);
    PiezoSound(p);
    //max - velocity = velocity range
    int piezoGain = (1024 - Piezo[p].velocity) + (Piezo[p].topValue*Piezo[p].velocity)>>10;
    piezoGain<<=9;
    EffectGain[p]->gain(piezoGain);//should be 6, but is too quit
    DEBUG_PRINT(piezoGain);
    Piezo[p].hit=0;
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
void PiezoSound(int numPiezo)
{
  int p = numPiezo;
  playFlashRaw[p]->play(serialFlash_Samples[Piezo[p].sample]);
  Serial.print("played Piezo ");
  Serial.println(numPiezo);
}
void piezoPreset()
{
  PiezoSetSample(0, 65);
  PiezoSetSample(1, 76);
  PiezoSetSample(2, 37);
  PiezoSetSample(3, 37);
}

