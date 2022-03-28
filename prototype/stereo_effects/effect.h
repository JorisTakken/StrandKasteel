#pragma once 
#include "sine.h"
#include "square.h"
#include "saw.h"

#include <iostream>

class Effect{
    public: 
        Effect(unsigned int samplerate);
        virtual ~Effect();

        // this is the function we will call in the Main!
        void applyEffect(float &input, float &output);
        void setDrywet(float newDryWet);
        float getDrywet();

        
    protected: 
        virtual void processEffect(float &input, float &output) = 0;
        float map(float input, int x1, int x2 , float min, float max);
        int msToSamps(float miliseconds);

        Oscillator* oscillator;
        int samplerate = 44100;
    
    private:
        float dryWet = 1;


        
};