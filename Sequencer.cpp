#include "Sequencer.h"
#include "effect_gain.h"
#include "piezos.h"
sequencer sequencer1;
IntervalTimer seqTimer;
/////////////////////////////////////////////////////////////////////////////////////////////////
//initialize.
//set the bpm, which also starts the sequencer
sequencer::sequencer()
{
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void sequencer::setbpm(uint16_t newbpm)
{
  oldbpm = bpm;
	
  if(abs(oldbpm - newbpm) < 5) return;
  bpm = newbpm;
	if(newbpm == 0)
	{
		seqTimer.end();
		Serial.println("Sequencer stopped");
	}
	else
	{
		uint32_t newTickTime = (1000*1000*60)/(newbpm*4);
		seqTimer.begin(sequencePlay,newTickTime);
		seqTimer.priority(255);//Default value of 128 clashes with another interrupt. Probably serial?
		Serial.print("Sequencer BPM changed:");
		Serial.println(newbpm);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//record and erase
void sequencer::recordHit(int piezo, int velocity)
{
   if(mode !=RECORD) return;
    currentTrack->data[currentTick][piezo] = velocity >> 8;
}
void sequencer::eraseHit(int piezo)
{
   if(mode !=ERASE) return;
    currentTrack->data[currentTick][piezo] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//play sequence
void sequencer::play()
{
	for(int r = 0; r < 8; r++)
	{
		//get the entry from the track
		if(currentTrack->data[currentTick][r] > 0)
		{
      Piezo[r].playSample(currentTrack->data[currentTick][r]<<8);
		}
	}
	currentTick+=1;
	//overflow:
	//reached the end of the track/measure.
	//if a next track is selected, play it.
	//reset the step to 0 
	if(currentTick > currentTrack->measure_ticks-1) 
	{
		if(nextTrack != NULL && nextTrack != currentTrack)
		{
			currentTrack = nextTrack;
		}
		currentTick = 0;
	}
}
//a small wrapper is needed because we can't pass class member functions as pointers
//so we pass a function that calls the sequence play member function
void sequencePlay()
{
	AudioNoInterrupts();
	sequencer1.play();
	AudioInterrupts();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
