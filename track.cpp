#include "track.h"
#include "Audio.h"
//called
void TrackClass::loadData(char* _filename)
{
	File inFile;
	inFile = SD.open(filename, FILE_READ);
	if(!inFile) 
	{
		Serial.print("File not found: ");
		Serial.println(_filename);
		return;
	}
	while (inFile.available())
	{
		uint8_t i = inFile.read();
		Serial.println(i);
	}
	return;
	//set the sequence name
	for(int i = 0;i<11;i++)
	{
		filename[i] = _filename[i];
	}
	//now: read!
	uint8_t fileversion = 0;
	fileversion = inFile.read();
	
	Serial.print("Fileversion: ");
	Serial.println(fileversion);
//	if(fileversion == 0)
	//{
		instruments= inFile.read();//instruments
		Serial.print("instruments: ");
		Serial.println(instruments);
		columns = inFile.read();//sequence length
		Serial.print("columns: ");
		Serial.println(columns);
		signature_upper = inFile.read();//meter 1
		signature_lower = inFile.read();//meter 2
		Serial.println("contents");
		for(int r = 0; r < 12; r++)
		{
			for(int c = 0;c<16;c++)
			{
				data[c][r] = inFile.read();
				Serial.print(data[c][r]);
				Serial.print(" \t ");
			}
			Serial.println();
		}
//	}
	inFile.close();
	Serial.println("Loaded data");
}
void TrackClass::saveData(char* _filename)
{
	AudioNoInterrupts();
	File outFile;
	SD.remove(_filename);
	outFile = SD.open(_filename, FILE_WRITE);
	if(!outFile) return;
	uint8_t fileversion = 0;
	outFile.write(fileversion);//file version
	outFile.write(instruments);//instruments
	outFile.write(columns);//sequence length
	outFile.write(signature_upper);//meter 1
	outFile.write(signature_lower);//meter 2
	Serial.println("contents");
	for(int r = 0; r < 12; r++)
	{
		for(int c = 0;c<16;c++)
		{
			outFile.write(data[c][r]);
			Serial.print(data[c][r]);
		}
		Serial.println();
	}
	outFile.close();
	Serial.println("file written");
	AudioInterrupts();
}

uint8_t TrackClass::getEntry(uint8_t _column, uint8_t _instrument)
{
	return data[_column][_instrument];
}
void TrackClass::setEntry(uint8_t _column, uint8_t _instrument, uint8_t _entry)
{
	data[_column][_instrument] = _entry;
}
TrackClass Track[16];//16 tracks, one for every trellis button

