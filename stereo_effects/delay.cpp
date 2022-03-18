#include "delay.h"


Delay::Delay(int size, int numSamplesDelay, float feedback) : Effect(samplerate),
                                                                size(size), numSamplesDelay(numSamplesDelay),
                                                                writePoint(0), readPoint(size - numSamplesDelay), 
                                                                feedback(feedback){ 
    while (numSamplesDelay > size) {
        std::cout << "MAG NIET, choose other delay!" << std::endl;
        std::cout << "kies maar : " << std::endl;
        int input;
        std::cin >> input;
        numSamplesDelay = input;
    }
    buffer = new float[size];
    for(int i = 0; i < size; i++) {
        buffer[i] = 0;
    }
}

Delay::~Delay(){
    delete [] buffer;
    buffer = nullptr;
}

void Delay::processEffect(float &input, float &output){
    buffer[writePoint++] = input + (output * feedback);
    writePoint = wrap(writePoint);
    
    output = buffer[readPoint++];
    readPoint = wrap(readPoint);
}

float Delay::getDistance(){   
    if(writePoint < readPoint) {
        int flip = writePoint;
        flip += size;
        return flip - readPoint;
    }
    return writePoint - readPoint;
}

float Delay::wrap(int point){
    if (point >= size){
        point -= size; 
    }
    return point;
}