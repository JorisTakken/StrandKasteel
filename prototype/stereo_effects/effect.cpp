#include "effect.h"

Effect::Effect(unsigned int samplerate){
}

Effect::~Effect(){
}

    // pointer to jack audio's in and output buffer
void Effect::applyEffect(float &input, float &output){
    // dry wet
    processEffect(input,output);
    output = output * (dryWet) + input * (1.0 - dryWet);
}

void Effect::setDrywet(float newDryWet){  
    float max = 1;
    float min = 0;
    while(newDryWet < 0 ||  newDryWet > 1.0){
        std::cout << "MAG NIET, choose dry wet form 0 - 1!" << std::endl;
        std::cout << "kies maar : " << std::endl;
        int input;
        std::cin >> input;
        newDryWet = input;
    }
    float value;
    float range = max - min; 
    value = range * newDryWet;
    value += min;
    this->dryWet = value;
}

float Effect::getDrywet(){
    return dryWet;
}

float Effect::map(float input, int x1, int x2 , float min, float max){
    // STARTING AT A X VALUE
    float value = (min * (x2 - input) + max * (input - x1)) / (x2 - x1);    
    return value;
}

int Effect::msToSamps(float miliseconds){
    return int((miliseconds * (samplerate / 1000.0)) + 0.5);
}