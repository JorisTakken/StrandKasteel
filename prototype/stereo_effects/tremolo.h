#pragma once 
#include "effect.h"
#include <iostream>

class Tremolo : public Effect{
    public: 
    // 0 = sine, 1 = saw, square = 2 
        enum Waveformtype {sine = 0,saw,square};
        
        Tremolo(Waveformtype waveform, float modFreq, float modDepht);
        ~Tremolo() override;

        void setModFreq(float freq);
        void setModDepht(float modDepht);
 
    protected: 
        void processEffect(float &input, float &output) override;
        float modDepht;
};