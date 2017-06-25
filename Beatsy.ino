//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Beatsy
//
//todo:
// - make a proper board
// - add trellis
// - add rotary switch to switch patch/sample
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Includes
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <debugtools.h>
#include <Wire.h>
#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <effect_gain.h>
#include <Encoder.h>

#include "routing.h"
#include "Piezos.h"
#include "FlashStorage.h"
#include "trellisdriver.h"
#include <Mux.h>
#include "TestTracks.h"
#include "sequencer.h"

#define DEBUG
const int FlashChipSelect = 6; // digital pin for flash chip CS pin
int16_t mainVolume;
int16_t sequencerBpm=100;
int16_t testValue2;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup the port expander
//used for the piezo reader
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupPortExpander()
{
  Serial.println("setup portexpander");
  Wire.begin();
  Wire.beginTransmission(0x20);
  Wire.write(0x00);//poort A register
  Wire.write(0x00);//poort A output
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x01);//poort B register
  Wire.write(0x00);//poort B output
  Wire.endTransmission();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//GPIO
//0     Multiplexer S0
//1     Multiplexer S1
//2     Multiplexer S2
//3     Rotary encoder A
//4     Rotary encoder B
//5     Trellis interrupt
//6     Flash Chip select
//7     SPI MOSI
//8
//9     Audio board BCLK
//10    SD chip select
//11    Audio board MCLK
//12    SPI MISO
//13    Audio board RX
//14    SPI clock
//15/A1 Audio board volume (there is a capacitor here)
//16/A2 Piezo analog input
//17    Multiplexer analog input A
//18    I2S SDA
//19    I2S SCL
//20
//21
//22    Audio board TX
//23    Audio board LRCLK
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupGPIO()
{
  Serial.println("setup GPIO");
  pinMode(A1,INPUT);//15 - Audio board volume
  pinMode(A2,INPUT);//16 - piezo analog input
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  SPI.setSCK(14);  // Audio shield has SCK on pin 14
  SPI.setMOSI(7);  // Audio shield has MOSI on pin 7
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup the multiplexer objects
//note: must be fully initialized to prevent null pointer errors
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupMultiplexers()
{
  Serial.println("setup Multiplexer");
  multiplexer1.init(0, 1, 2, 17);
  multiplexer1.assign(0,&mainVolume);
  multiplexer1.assign(1,&sequencerBpm);
  multiplexer1.assign(2,&testValue2);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup the tracks, fill them with preprogrammed stuff
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupTracks()
{
  init_track0();
  init_track1();
  init_track2();
  init_track3();
  init_track4();
  init_track5();
  init_track6();
  init_track7();
  init_track8();
  init_track9();
  init_track10();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup the mixer objects
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupMixers()
{
  Serial.println("setup mixers");
  //left
  mixer1L.gain(0,0.25);
  mixer1L.gain(1,0.25);
  mixer1L.gain(2,0.25);
  mixer1L.gain(3,0.25);
  mixer2L.gain(0,0.25);
  mixer2L.gain(1,0.25);
  mixer2L.gain(2,0.25);
  mixer2L.gain(3,0.25);
  //right
  mixer1R.gain(0,0.25);
  mixer1R.gain(1,0.25);
  mixer1R.gain(2,0.25);
  mixer1R.gain(3,0.25);
  mixer2R.gain(0,0.25);
  mixer2R.gain(1,0.25);
  mixer2R.gain(2,0.25);
  mixer2R.gain(3,0.25);

  mixerL.gain(2,0.0);//I2S input: nothing yet but noise
  mixerR.gain(2,0.0);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Audio volume and bpm
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void updateGlobalAudioVars()
{
  float i = mainVolume>>4;
  audioShield.volume(i/64.0f);

  int j = (sequencerBpm>>3) + 60;
  sequencer1.setbpm(j);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//readoutPiezo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void readoutPiezo()
{
  static int currentPiezo;//current Piezo, 0-7
  Piezo[currentPiezo].preRead();
  delayMicroseconds(50);
  int hit = Piezo[currentPiezo].doState();//then read
  drainPiezos();//and drain
  if(hit > 0)
  {
    multiplexer1.assign(2,&Piezo[currentPiezo].sampleGain);
    multiplexer1.assign(3,&Piezo[currentPiezo].velocity);
    sequencer1.recordHit(currentPiezo, hit);
  }
  currentPiezo+=1;
  if(currentPiezo > numPiezos-1) currentPiezo = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(40);
  setupGPIO();
  trellisSetup();
  setupFlash(FlashChipSelect);
  setupPortExpander();
  setupMixers();
  setupMultiplexers();
  setupPiezos();
  setupTracks();
  
  audioShield.enable();
  audioShield.volume(0.8);
  sequencer1.setCurrentTrack(&Track[10]);//select preprogrammed track with only hats
  sequencer1.setbpm(100);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Main loop
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{
  readoutPiezo();
  multiplexer1.read();
  updateGlobalAudioVars();
  int i = trellisReadout();
  if(i != -1) sequencer1.setNextTrack(&Track[i]);
}
