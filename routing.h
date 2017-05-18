#ifndef routing_h
#define routing_h

#include <effect_gain.h>
#include "Mux.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Audio routing
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw7; //xy=97,405
AudioPlaySerialflashRaw  playFlashRaw8; //xy=98,446
AudioPlaySerialflashRaw  playFlashRaw6; //xy=99,368
AudioPlaySerialflashRaw  playFlashRaw5; //xy=100,330
AudioPlaySerialflashRaw  playFlashRaw3; //xy=101,234
AudioPlaySerialflashRaw  playFlashRaw4; //xy=101,271
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=102,153
AudioPlaySerialflashRaw  playFlashRaw2; //xy=104,201
AudioEffectGain          gain1;
AudioEffectGain          gain2;
AudioEffectGain          gain3;
AudioEffectGain          gain4;
AudioEffectGain          gain5;
AudioEffectGain          gain6;
AudioEffectGain          gain7;
AudioEffectGain          gain8;
AudioMixer4              mixer1L;         //xy=295,175
AudioMixer4              mixer2R; //xy=298,451
AudioMixer4              mixer1R; //xy=300,265
AudioMixer4              mixer2L; //xy=300,351
AudioInputI2S            i2s_input;           //xy=300,525
AudioMixer4              mixerR; //xy=497,388
AudioMixer4              mixerL;         //xy=502,279
AudioOutputI2S           i2s_output;           //xy=666,330

AudioConnection          patchCord101(playFlashRaw1, 0, gain1, 0);
AudioConnection          patchCord102(playFlashRaw2, 0, gain2, 0);
AudioConnection          patchCord103(playFlashRaw3, 0, gain3, 0);
AudioConnection          patchCord104(playFlashRaw4, 0, gain4, 0);
AudioConnection          patchCord105(playFlashRaw5, 0, gain5, 0);
AudioConnection          patchCord106(playFlashRaw6, 0, gain6, 0);
AudioConnection          patchCord107(playFlashRaw7, 0, gain7, 0);
AudioConnection          patchCord108(playFlashRaw8, 0, gain8, 0);

AudioConnection          patchCord1(gain7, 0, mixer2L, 2);
AudioConnection          patchCord2(gain7, 0, mixer2R, 2);
AudioConnection          patchCord3(gain8, 0, mixer2L, 3);
AudioConnection          patchCord4(gain8, 0, mixer2R, 3);
AudioConnection          patchCord5(gain6, 0, mixer2L, 1);
AudioConnection          patchCord6(gain6, 0, mixer2R, 1);
AudioConnection          patchCord7(gain5, 0, mixer2L, 0);
AudioConnection          patchCord8(gain5, 0, mixer2R, 0);
AudioConnection          patchCord9(gain3, 0, mixer1L, 2);
AudioConnection          patchCord10(gain3, 0, mixer1R, 2);
AudioConnection          patchCord11(gain4, 0, mixer1L, 3);
AudioConnection          patchCord12(gain4, 0, mixer1R, 3);
AudioConnection          patchCord13(gain1, 0, mixer1L, 0);
AudioConnection          patchCord14(gain1, 0, mixer1R, 0);
AudioConnection          patchCord15(gain2, 0, mixer1L, 1);
AudioConnection          patchCord16(gain2, 0, mixer1R, 1);
AudioConnection          patchCord17(mixer1L, 0, mixerL, 0);
AudioConnection          patchCord18(mixer2R, 0, mixerR, 1);
AudioConnection          patchCord19(mixer1R, 0, mixerR, 0);
AudioConnection          patchCord20(mixer2L, 0, mixerL, 1);
AudioConnection          patchCord21(i2s_input, 0, mixerL, 2);
AudioConnection          patchCord22(i2s_input, 1, mixerR, 2);
AudioConnection          patchCord23(mixerR, 0, i2s_output, 1);
AudioConnection          patchCord24(mixerL, 0, i2s_output, 0);
// GUItool: end automatically generated code

AudioPlaySerialflashRaw *playFlashRaw[8] = {&playFlashRaw1,&playFlashRaw2,&playFlashRaw3,&playFlashRaw4,&playFlashRaw5,&playFlashRaw6,&playFlashRaw7,&playFlashRaw8};
AudioEffectGain *EffectGain[8] = {&gain1,&gain2,&gain3,&gain4,&gain5,&gain6,&gain7,&gain8};
AudioControlSGTL5000 audioShield;

#endif
