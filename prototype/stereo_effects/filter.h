#include <iostream>
#include "effect.h"

class Filter : public Effect{
    public:
        enum filterType {lowpass = 0, highpass = 1};

        Filter(filterType type, float cutoff, float LFOrate);
        ~Filter();

        void processEffect(float& input, float &output) override;
        void setCutoff(float newCutoff);
        float LFOcutoff(float LFOrate);

    protected: 
        float lastSample = 0;
        filterType type;
        float cutoff;
        float LFOrate = 0;
        float change;

};

