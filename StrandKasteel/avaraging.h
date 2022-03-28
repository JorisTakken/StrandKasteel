#include <iostream>

class Avaraging{
    public:
        Avaraging();
        ~Avaraging();

        void setSmoothFactor(float smoothingFactor);
        float smooth(float input);
        float linMap(float input, int x1, int x2, float min, float max);
    
    protected:
        float smoothingFactor;
        float lastSample;
        float avarage;
        float* history;
        int historyIndex = 0;
};