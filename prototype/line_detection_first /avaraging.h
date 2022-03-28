#include <iostream>

class Avaraging{
    public:
        Avaraging(float smoothingFactor);
        ~Avaraging();

        float smooth(float input);
    
    protected:
        float smoothingFactor;
        float lastSample;
        float avarage;
        float* history;
        int historyIndex = 0;
};