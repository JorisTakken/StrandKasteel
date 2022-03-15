#include "chorus.h"
#include "sine.h"

Chorus::Chorus(float samplerate, float modDepth, float feedback, float modSpeed) : Effect(),
  m_modDepth(modDepth),
  cbuffer(44100, 22050)
  {
  this->feedback = feedback;
  this->samplerate = samplerate;
  delayMS(0);

  m_osc = new Sine(modSpeed, samplerate);

}

Chorus::~Chorus() {
  delete m_osc;

  m_osc = nullptr;

}

void Chorus::applyEffect(float& input, float& output){

  delaytime = (m_osc->genNextSample() + 3) ; //add amount changer
  delayMS(delaytime);
  output = m_modSignal + input;

  cbuffer.write((input + output * feedback) * 0.5);

  m_modSignal = cbuffer.read() ;

  // m_modSignal *= m_modDepth;
  // m_modSignal += 1.0 - m_modDepth;

}

void Chorus::delayMS(float delayInMS){
  delayInSamps = delayInMS * (samplerate / 1000);

  cbuffer.setNumSamplesDelay(delayInSamps);

}

void Chorus::delaySamps(float delaySamps){
  cbuffer.setNumSamplesDelay(delaySamps);

}

void Chorus::setFeedback(float feedback1){
  this->feedback = feedback1;
}
