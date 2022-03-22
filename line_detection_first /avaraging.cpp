#include "avaraging.h"

Avaraging::Avaraging(float smoothingFactor) : smoothingFactor(smoothingFactor){
}

Avaraging::~Avaraging(){
}

float Avaraging::smooth(float input){
    float avarage += (input) / 2; 
    // lastSample = avarage; 
    // std::cout << avarage << std::endl;
    return avarage;
}















// int pot1 = A1;
// int pot1V;
// int pot1MIDI = 0;
// int _pot1MIDI = 0;

// const int historyLenght1 = 20;
// int pot1History[historyLenght1];
// int historyIndex1 = 0;

//   //Voor Pot1-------------------------------------------------
//   pot1History[historyIndex1] = pot1V;
//   historyIndex1++; 
//   historyIndex1 = historyIndex1 % historyLenght1;
//   int avarage1 = 0; 
//   for (int i = 0; i < historyLenght1; i ++){
//     avarage1 = avarage1 + pot1History[i];
//   }
//   avarage1 = avarage1 / historyLenght1;
  
//   pot1MIDI = avarage1 / 8;
//   //voorPot1==========================================