#include "tremolo.h"


Tremolo::Tremolo(Waveformtype waveform, float modFreq,float modDepht) : Effect(samplerate),
    modDepht(modDepht){
    switch (waveform) {
    case Waveformtype::sine:
    {
    oscillator = new Sine(modFreq, samplerate);
    break;
    }
    case Waveformtype::saw:{
    oscillator = new Saw(modFreq, samplerate);
    break;
    }
    case Waveformtype::square:{
    oscillator = new Square(modFreq, samplerate);
    break;
        }
    }
}

Tremolo::~Tremolo(){
    delete oscillator;
    oscillator = nullptr;
}

void Tremolo::setModFreq(float freq){
    oscillator->setFrequency(freq);
}

void Tremolo::setModDepht(float newModDepht){
    modDepht = newModDepht;
}

void Tremolo::processEffect(float &input, float &output){
    // modSignal = range 0 - 1 ==== oscillator in range van -1 tot 1 
    float tremolo = (oscillator->genNextSample() + 1.0) * 0.5;
    tremolo *= modDepht;
    tremolo += 1.0 - modDepht;
    output = input * tremolo;
}