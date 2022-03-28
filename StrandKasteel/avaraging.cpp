#include "avaraging.h"

Avaraging::Avaraging(){
    
}

Avaraging::~Avaraging(){
}

void Avaraging::setSmoothFactor(float smoothingFactor){
    this->smoothingFactor = smoothingFactor;
    history = new float[smoothingFactor];
    for(int i = 0; i<smoothingFactor; i++ ){
        history[i] = 0;
    }
}

float Avaraging::smooth(float input){
    history[historyIndex] = input;
    historyIndex++; 

    if (historyIndex > smoothingFactor){
        historyIndex = 0;
    }
    for (int i = 0; i < smoothingFactor; i ++){
      avarage += history[i];
    }

    avarage = avarage / smoothingFactor;
    return avarage;
}

float Avaraging::linMap(float input, int x1, int x2, float min, float max){
  // STARTING AT A X VALUE
    float value = (min * (x2 - input) + max * (input - x1)) / (x2 - x1);
    return value;
}



