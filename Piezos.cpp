#include "piezos.h"
#define DEBUG

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Read piezo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

void piezoInput::preRead()
{
  Wire.beginTransmission(0x20);
  Wire.write(0x12);
  Wire.write(physicalInput);
  Wire.endTransmission();
}
void piezoInput::incrementSample()
{
  sample+=1;
  if(sample >= serialFlash_nSamples) sample = 0;
}
void piezoInput::decrementSample()
{
  sample-=1;
  if(sample < 0) sample = serialFlash_nSamples-1;
}
int piezoInput::doState()
{
  int hit = 0;
  int piezoRiseThreshold = 50;
  int piezoFallThreshold = 40;
  LastValue = Value;
  Value = analogRead(A2);
  Direction = Value-LastValue;
  //state machine
  if(State == idle && Value > piezoRiseThreshold)
  {
    State = rise;
  }
  if(State == rise && Direction < 0)
  {
    State = fall;
    topValue = min(Value,1024)-piezoRiseThreshold;
    //max - velocity = velocity range
    int hitGain = ((1024 - velocity) <<10) + (topValue*velocity);
    playSample(hitGain);
    hit = hitGain;
    DEBUG_PRINT(hitGain);
  }
  if(State == fall && Value < piezoFallThreshold)
  {
    State = idle;
  }
  return hit;
}
void piezoInput::setSample(uint16_t numSample)
{
  sample = numSample;
}
void drainPiezos()
{ 
  //select the Input to drain.
  //The outputs of the MCP23017 are directly connected to the bases of the transistors
  //write it to portB
  static uint8_t drainByte;
  for(int i=0;i<numPiezos;i++)
  {
     drainByte |= (Piezo[i].getState() == fall) << i;
     drainByte &= 0xFF ^ ((Piezo[i].getState() != fall) << i);
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
//todo:
// - linking pads together, so one can mute the other
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void piezoInput::playSample(uint16_t velocity)
{
  static uint32_t sampleCounts[8];
  static uint32_t sampleCountup=0;
  char* filename = serialFlash_Samples[sample];
  uint32_t lowestSampleCount=0xFFFFFFFF;
  int oldestSampler = -1;
  int chosenSampler = -1;
  for(int i=0;i<8;i++)
  {
    if(!playFlashRaw[i].isPlaying())
    {
      chosenSampler = i;
    }
    //also record which one is the oldest
    if(lowestSampleCount > sampleCounts[i])
    {
      lowestSampleCount = sampleCounts[i];
      oldestSampler = i;
    }
  }
  //all busy
  //no quiet sampler found? play the oldest
  if(chosenSampler == -1) chosenSampler = oldestSampler;
  playFlashRaw[chosenSampler].play(filename);
  velocity = (velocity*sampleGain)>>10;
  gainer[chosenSampler].gain(velocity);
  sampleCounts[chosenSampler] = sampleCountup;
  sampleCountup+=1;
}
void setupPiezos()
{
  Piezo[0].setSample(37);//kick
  Piezo[0].setPhysicalInput(0);
  Piezo[1].setSample(76);//rim
  Piezo[1].setPhysicalInput(1);
  Piezo[2].setSample(0);//hat
  Piezo[2].setPhysicalInput(2);
  Piezo[3].setSample(65);//ride
  Piezo[3].setPhysicalInput(3);
  Piezo[4].setPhysicalInput(4);
  Piezo[5].setPhysicalInput(5);
  Piezo[6].setPhysicalInput(6);
  Piezo[7].setPhysicalInput(7);
}

