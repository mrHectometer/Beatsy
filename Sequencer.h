// Sequencer.h

#ifndef _SEQUENCER_h
#define _SEQUENCER_h
#include "track.h"
#include "arduino.h"

extern IntervalTimer seqTimer;
typedef enum  {IDLE=0, PLAY=1, RECORD=2, ERASE=3} SequenceMode_t;

class sequencer
{
 protected:
	volatile TrackClass *currentTrack;
	volatile TrackClass *nextTrack;
	uint16_t bpm = 120;
  uint16_t oldbpm;
	volatile int currentTick;
  SequenceMode_t mode = IDLE;
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
  void recordHit(int piezo, int velocity);
  void eraseHit(int piezo);
  void setRecord()
  {
    mode = RECORD;
  }
  void setPlay()
  {
    mode = PLAY;
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

