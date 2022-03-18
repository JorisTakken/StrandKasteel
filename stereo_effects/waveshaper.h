#include <iostream>
#pragma once 
#include "math.h"
#include "bufferDebugger.h"
#include "sine.h"
#include "saw.h"
#include "square.h"
#include "oscillator.h"
#include "effect.h"

#include <cstdlib>
#include <ctime>


class Waveshaper : public Effect{
    public:
        Waveshaper(int buffersize);
        ~Waveshaper();

        enum WaveChoise {sine = 0, saw, square};

        void genWaveshape(float sharpness);
        void genWaveshapeOscillator(WaveChoise wave, float freq);   
        void genWaveshapeNoise(float noiseVal,int i);

        void plot_waveshaper();

    protected:
        void processEffect(float &input, float &output) override;

        int buffersize;
        float* wavetableBuffer;
};

