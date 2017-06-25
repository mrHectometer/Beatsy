#include <Wire.h>
#include "trellisdriver.h"

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

void trellisSetup()
{
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);
}
elapsedMillis TrellisReadout;
int trellisReadout()
{
  if(TrellisReadout < 30)return -1;
  TrellisReadout = 0;
  //if a button was pressed or released
  if(trellis.readSwitches())
  {
    //run through every button
     for (uint8_t i=0; i<numKeys; i++)
     {
        //if pressed
        if(trellis.justPressed(i))
        {
          //first clear all the leds
          for (uint8_t j=0; j<numKeys; j++)
          {
            trellis.clrLED(j);
          }
          //serial plot which one was pressed
          Serial.print("v"); Serial.println(i);
          trellis.setLED(i);//turn the led on
          trellis.writeDisplay();//write it to the display
          return i;
        }
     }
  }
  return -1;
}

