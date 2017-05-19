#ifndef routing_h
#define routing_h

#include <effect_gain.h>
#include "Mux.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Audio routing
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
AudioPlaySerialflashRaw  playFlashRaw[8];
AudioEffectGain          gainer[8];
AudioMixer4              mixer1L;
AudioMixer4              mixer2R;
AudioMixer4              mixer1R;
AudioMixer4              mixer2L;
AudioInputI2S            i2s_input;
AudioMixer4              mixerR;
AudioMixer4              mixerL;
AudioOutputI2S           i2s_output;

AudioConnection          patchCord101(playFlashRaw[0], 0, gainer[0], 0);
AudioConnection          patchCord102(playFlashRaw[1], 0, gainer[1], 0);
AudioConnection          patchCord103(playFlashRaw[2], 0, gainer[2], 0);
AudioConnection          patchCord104(playFlashRaw[3], 0, gainer[3], 0);
AudioConnection          patchCord105(playFlashRaw[4], 0, gainer[4], 0);
AudioConnection          patchCord106(playFlashRaw[5], 0, gainer[5], 0);
AudioConnection          patchCord107(playFlashRaw[6], 0, gainer[6], 0);
AudioConnection          patchCord108(playFlashRaw[7], 0, gainer[7], 0);

AudioConnection          patchCord1(gainer[6], 0, mixer2L, 2);
AudioConnection          patchCord2(gainer[6], 0, mixer2R, 2);
AudioConnection          patchCord3(gainer[7], 0, mixer2L, 3);
AudioConnection          patchCord4(gainer[7], 0, mixer2R, 3);
AudioConnection          patchCord5(gainer[5], 0, mixer2L, 1);
AudioConnection          patchCord6(gainer[5], 0, mixer2R, 1);
AudioConnection          patchCord7(gainer[4], 0, mixer2L, 0);
AudioConnection          patchCord8(gainer[4], 0, mixer2R, 0);
AudioConnection          patchCord9(gainer[2], 0, mixer1L, 2);
AudioConnection          patchCord10(gainer[2], 0, mixer1R, 2);
AudioConnection          patchCord11(gainer[3], 0, mixer1L, 3);
AudioConnection          patchCord12(gainer[3], 0, mixer1R, 3);
AudioConnection          patchCord13(gainer[0], 0, mixer1L, 0);
AudioConnection          patchCord14(gainer[0], 0, mixer1R, 0);
AudioConnection          patchCord15(gainer[1], 0, mixer1L, 1);
AudioConnection          patchCord16(gainer[1], 0, mixer1R, 1);
AudioConnection          patchCord17(mixer1L, 0, mixerL, 0);
AudioConnection          patchCord18(mixer2R, 0, mixerR, 1);
AudioConnection          patchCord19(mixer1R, 0, mixerR, 0);
AudioConnection          patchCord20(mixer2L, 0, mixerL, 1);
AudioConnection          patchCord21(i2s_input, 0, mixerL, 2);
AudioConnection          patchCord22(i2s_input, 1, mixerR, 2);
AudioConnection          patchCord23(mixerR, 0, i2s_output, 1);
AudioConnection          patchCord24(mixerL, 0, i2s_output, 0);

AudioControlSGTL5000 audioShield;

#endif
