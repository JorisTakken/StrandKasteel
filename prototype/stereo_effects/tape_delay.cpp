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
  // output = input;
  //add modulation to delayMS
  float modSig = ((osc->genNextSample() + 1) * 0.5);
  setDelayMS(delayMS + modSig);

  //filter
  output = ((oscFilter->genNextSample()) * input) + ((1 - oscFilter->genNextSample()) * lastSample);
  lastSample = input;

  output = input + modulation;

  //write to buffer
  circ->write(input + (output * feedback));

  //interpolate
  float interpol = circ->read() - circ->readNext();
  modulation = map(interpol, 0, 1, circ->read(), circ->readNext());
  
  //saturation
  // output = sin(output * drive); // sine saturation
  // input = tanh(input * drive); //tanH saturation

}

void TapeDelay::setDelayMS(float delayMS){
  int delaySamps = msToSamps(delayMS);
  circ->setDelaySamps(delaySamps);
}

void TapeDelay::setFeedback(float newFeedback){
  feedback = newFeedback;
}
