#include "FlashStorage.h"

char serialFlash_Samples[256][20];
int serialFlash_nSamples;
int serialFlash_Samples_List()
{
  SerialFlash.opendir();
  int nFiles = 0;
  uint32_t filesize;
  while (1) 
  {
    if (SerialFlash.readdir(serialFlash_Samples[nFiles], sizeof(serialFlash_Samples[nFiles]), filesize)) 
    {
       Serial.print("Sample ");
       Serial.print(nFiles);
       Serial.print(": ");
       Serial.println(serialFlash_Samples[nFiles]);
       nFiles+=1;
    }
    else 
    {
       break; // no more files
    }
  }
  return nFiles;
}
int setupFlash(int FlashChipSelect)
{
  Serial.println("Setup Flash storage");
  if (!SerialFlash.begin(FlashChipSelect)) {
    Serial.println("Unable to access SPI Flash chip");
  }
  serialFlash_nSamples = serialFlash_Samples_List();
  Serial.print(serialFlash_nSamples);
  Serial.println(" files found on flash");
}

