#include "tape_delay.h"

//Leeftijd tape aanpassen
//parameter in instalatie oplopen

TapeDelay::TapeDelay(int samplerate, int delayMS, float feedback, float modFrequency, float drive) :
  Effect(samplerate),delayMS(delayMS), feedback(feedback), drive(drive)
{

  int numSamples = msToSamps(delayMS);
  this->numSamples = numSamples;


  osc = new Sine(modFrequency, samplerate);
  oscFilter = new Sine(0.5, samplerate);
  circ = new CircBuffer(samplerate, numSamples);
}

TapeDelay::~TapeDelay()
{
  delete osc;
  delete circ;
  osc = nullptr;
  circ = nullptr;
}


void TapeDelay::processEffect(float &input, float &output)
{

  float tempSample = sin(input * drive);
  //add modulation to delayMS
  float modSig = (osc->genNextSample() + 1);
  setDelayMS(delayMS + modSig);


  //filter
  output = ((oscFilter->genNextSample()) * tempSample) + ((1 - oscFilter->genNextSample()) * lastSample);
  lastSample = input;

  output = input + modulation;

  //write to buffer
  circ->write(input + (output * feedback));

  //interpolate
  float interpol = circ->read() - circ->readNext();
  modulation 





}

void TapeDelay::setDelayMS(float delayMS){
  int delaySamps = msToSamps(delayMS);
  circ->setDelaySamps(delaySamps);
}

void TapeDelay::setFeedback(float newFeedback){
  feedback = newFeedback;
}
