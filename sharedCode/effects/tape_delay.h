#pragma once
#include <iostream>
#include <cmath>
#include "effect.h"
#include "oscillator.h"
#include "sine.h"
#include "circBuffer.h"

typedef unsigned int uint;

class TapeDelay : public Effect
{
public:
  TapeDelay(int samplerate, int delayMS, float feedback, float modFrequency, float drive);
  ~TapeDelay();

  void processEffect(float& input, float &ouput) override;

  void setDelayMS(float delayMS);
  void setFeedback(float newFeedback);
  void setDrive(float newDrive);
  void setModFreq(float newModFreq);



protected:
  Oscillator* osc;
  Oscillator* oscFilter;
  CircBuffer* circ;
  int numSamples;
  int delayMS;
  float modFrequency;
  float feedback;
  float drive;
  float modulation;
  float lastSample = 0;

};
