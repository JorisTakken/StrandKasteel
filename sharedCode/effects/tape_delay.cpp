#include "tape_delay.h"

//Leeftijd tape aanpassen
//parameter in instalatie oplopen

TapeDelay::TapeDelay(int samplerate, int delayMS, float feedback, float modFrequency, float drive) :
  Effect(samplerate),delayMS(delayMS), feedback(feedback), drive(drive)
{

  int numSamples = msToSamps(delayMS);
  this->numSamples = numSamples;
  this->modFrequency = modFrequency;
  this->feedback = feedback;
  this->drive = drive;

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

  float tempSample = sin((input * drive) * 0.5);
  //add modulation to delayMS
  float modSig = (osc->genNextSample() + 1);
  setDelayMS(delayMS + modSig);

  output = input + modulation;

  //write to buffer
  circ->write(tempSample + (output * feedback));

  //interpolate
  float interpol = circ->read() - circ->readNext();
  modulation = map(interpol, 0, 1, circ->read(), circ->readNext());


}

void TapeDelay::setDelayMS(float delayMS){
  int delaySamps = msToSamps(delayMS);
  circ->setDelaySamps(delaySamps);
}

void TapeDelay::setFeedback(float newFeedback){
  feedback = newFeedback;
}

void TapeDelay::setDrive(float newDrive){
  drive = newDrive;
}

void TapeDelay::setModFreq(float newModFreq){
  modFrequency = newModFreq;
}
