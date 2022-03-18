#include "filter.h"

Filter::Filter(filterType type, float cutoff, float LFOrate) : Effect(samplerate){
    setCutoff(cutoff);
    oscillator = new Sine(LFOrate,samplerate);
    switch (type) {
        case filterType::lowpass: {
            change = -1;
            break;
            }
        case filterType::highpass: {
            change = 1;
            break;
        }
    } 
}

Filter::~Filter(){
}


void Filter::processEffect(float& input, float &output){
    output = ((0.5 + 0.5-cutoff) * input) + (change * (cutoff * lastSample)); 
    lastSample = input; 
    setCutoff((oscillator->genNextSample() + 1) * 0.5);
}

void Filter::setCutoff(float newCutoff){
    this->cutoff = newCutoff * 0.5;
}
