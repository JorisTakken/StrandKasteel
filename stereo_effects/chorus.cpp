#include "chorus.h"

Chorus::Chorus(float modFreq, float modDepth, int delayMS, float feedback, float samplerate) : Effect(samplerate),
                                                                                                modDepth(modDepth),feedback(feedback),
                                                                                                delayMS(delayMS)
{
    int delaySamps = msToSamps(delayMS);
    this->delaySamps = delaySamps;
    circBuffer = new CircBuffer(samplerate,delaySamps+4000);
    oscillator = new Sine(modFreq,samplerate);
}

Chorus::~Chorus(){
    delete circBuffer;
    circBuffer = nullptr;
    delete oscillator;
    oscillator = nullptr;
}

void Chorus::processEffect(float &input, float &output){
    float modSig = (oscillator->genNextSample() + 1) /2;
    setDelayMS(modSig * delayMS);

    output = input + modulation;
    circBuffer->write(input + (output * feedback));

    float interpolation = circBuffer->read() - circBuffer->readNext();

    modulation = map(interpolation,0,1,circBuffer->read(),circBuffer->readNext());
    modulation *= modDepth;
    modulation += 1.0 - modDepth;
}

void Chorus::setDelayMS(float delayMilsec){
    int delayInSamps = msToSamps(delayMilsec);
    circBuffer->setDelaySamps(delayInSamps);
}

