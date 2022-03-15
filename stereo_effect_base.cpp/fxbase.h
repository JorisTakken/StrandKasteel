#pragma once
#include <iostream>

class Effect
{
public:

  Effect(float dryWet = 1);
  virtual ~Effect();

  float processFrame(float& input, float& output);

  float getSample();
  void setDryWet(float dryWet);

protected:

  virtual void applyEffect(float& input, float& output) = 0;

private:
  float dryWet;
  float wetDry;
  float m_sample;

};
