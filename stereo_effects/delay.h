#pragma once 
#include "effect.h"
#include <iostream>

class Delay : public Effect{
    public:
        Delay(int size, int delayTime, float feedback);
        ~Delay() override;

        float getDistance();

    protected: 
        void processEffect(float &input, float &output) override;

        int size;
        int numSamplesDelay;
        float feedback;

        float* buffer;
        
        int writePoint;
        int readPoint;

    private:
        inline float wrap(int point);

};

