// Sequencer.h

#ifndef _SEQUENCER_h
#define _SEQUENCER_h
#include "track.h"
#include "arduino.h"

extern IntervalTimer seqTimer;

class sequencer
{
 protected:
	volatile TrackClass *currentTrack;
	volatile TrackClass *nextTrack;
	uint16_t bpm = 120;
	volatile int currentTick;

 public:
	
	sequencer();
	void setNextTrack(TrackClass* _Track)
	{
		_Track->set_measure_ticks();
		nextTrack = _Track;
	}
	void setCurrentTrack(TrackClass* _Track)
	{
		_Track->set_measure_ticks();
		currentTrack = _Track;
	}
	//void
	void play();
	void setbpm(uint16_t newbpm);
	int getbpm()
	{
		return bpm;
	}
};
extern sequencer sequencer1;
void sequencePlay();
#endif

