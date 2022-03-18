#include "waveshaper.h"



Waveshaper::Waveshaper(int buffersize) : Effect(44100), 
    buffersize(buffersize){
    wavetableBuffer = new float[buffersize];
}

Waveshaper::~Waveshaper(){
    delete wavetableBuffer;
}

void Waveshaper::genWaveshapeOscillator(WaveChoise wave, float freq){
    switch(wave){
        case WaveChoise::sine:{
            oscillator = new Sine(freq, buffersize);
            break;
        }
        case WaveChoise::saw:{
            oscillator = new Saw(freq, buffersize);
            break;
        }
        case WaveChoise::square:{
            oscillator = new Square(freq, buffersize);
            break;
        }
    }
        
        for (int i = 0; i < buffersize; i++){
            wavetableBuffer[i] = oscillator->genNextSample();
        }

        delete oscillator;
        oscillator = nullptr;
}

void Waveshaper::genWaveshapeNoise(float noiseVal, int i){
    float noise = (float)(noiseVal / 1000);
    noise = (noise / 10) * 5;
    if (noise > 1){
        noise = 1;
    } 
    else if (noise < -1){
        noise = -1;
    }
    // noise = map(noise, i, i+1, -1, 1);
    // float noise = map(noiseVal, i, i+1, -1.0f, 1.0f);
    wavetableBuffer[i] = noise;
}

void Waveshaper::genWaveshape(float sharpness){
    // THANKS TO CISKA MARC AND Pirkle 2013, "Designing Audio Effect Plug-ins in C++" p. 497
    float normalizeFactor = 1.0f / atan(sharpness);
    for(int i = 0; i < buffersize; i++) {
        float mappedVal = map((float)i, 0, buffersize, -1.0f, 1.0f);
        wavetableBuffer[i] = normalizeFactor * atan(sharpness * mappedVal);
  }
}

void Waveshaper::processEffect(float &input, float &output){
    // van CISKA
    float index = (input + 1) * (buffersize/2);
    int i = (int) index;
    float indexDecimal = index - float(i);
    output = (indexDecimal,0,1, wavetableBuffer[i], wavetableBuffer[i + 1]);
}


void Waveshaper::plot_waveshaper(){
    BufferDebugger::writeToFile(wavetableBuffer, buffersize, "output.csv");
}