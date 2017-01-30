//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Beatsy
//
//todo:
// - Piezo input 3 doesn't drain
// - make a proper board
// - add trellis and sequencer
// - add mux board and volume buttons
// - add rotary switch to switch patch/sample
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Includes
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

#define DEBUG
#include "debugutils.h"
#include <Wire.h>
#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "routing.h"
#include "Piezos.h"
#include "FlashStorage.h"
#include <effect_gain.h>


const int FlashChipSelect = 6; // digital pin for flash chip CS pin


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup the port expander
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
//0
//1
//2
//3
//4
//5
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
//17
//18    I2S SDA
//19    I2S SCL
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
  
  mixer1R.gain(0,0.25);
  mixer1R.gain(1,0.25);
  mixer1R.gain(2,0.25);
  mixer1R.gain(3,0.25);
  mixer2R.gain(0,0.25);
  mixer2R.gain(1,0.25);
  mixer2R.gain(2,0.25);
  mixer2R.gain(3,0.25);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Setup
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(80);
//  while(!Serial) ;
  delay(100);
  setupGPIO();
  setupFlash(FlashChipSelect);
  setupPortExpander();
  setupMixers();
  piezoPreset();
  audioShield.enable();
  audioShield.volume(0.6);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Main loop
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int currentPiezo;//current Piezo, 0-7
void loop() 
{
  //first select the piezo with prereadpiezo
  //then wait a bit
  preReadPiezo(currentPiezo);
  delayMicroseconds(50);
  PiezoState(currentPiezo);//then read
  drainPiezos();//and drain
  
  currentPiezo+=1;
  if(currentPiezo > 3) currentPiezo = 0;
}
