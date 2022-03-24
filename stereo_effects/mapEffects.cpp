#include "jack_module.h"
#include <string>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <iostream>

#include "chorus.h"
#include "filter.h"
#include "tremolo.h"
#include "sine.h"
#include "tape_delay.h"

unsigned long chunksize = 256;
JackModule jack;
float samplerate = 44100;

bool running = true;

int main(int argc, char **argv){
  jack.init(argv[0]);
  jack.autoConnect();

  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);

  float *inbuffer = new float[chunksize];
  float *outbuffer = new float[chunksize];

    Effect* TapeDelayL = new TapeDelay(samplerate, 100, 0.4, 3, 5); // size, delayMS, feedback, modFreq, Drive
    Effect* TapeDelayR = new TapeDelay(samplerate, 500, 0.4, 3, 2);

    Effect* FilterL = new Filter(Filter::filterType::highpass,1,0); //filterType, cutoff, LFOrate
    Effect* FilterR = new Filter(Filter::filterType::highpass,1,0);

    Effect* ChorusL = new Chorus(1,1,100,0.0,samplerate);// modFreq, modDepth, delayMS, feedback, samplerate
    Effect* ChorusR = new Chorus(1,1,100,0.0,samplerate);

    TapeDelayL->setDrywet(0.5);
    FilterL->setDrywet(1);
    ChorusL->setDrywet(0.5);

    TapeDelayR->setDrywet(0.5);
    FilterR->setDrywet(1);
    ChorusR->setDrywet(0.5);


    float outbufR;
    float outbufR2;
    float outbufL;
    float outbufL2;

  do{
    jack.readSamples(inbuffer,chunksize);
    for(unsigned int x=0; x<chunksize; x++)
    {
      TapeDelayL->applyEffect(inbuffer[x], outbufR);
      TapeDelayR->applyEffect(inbuffer[x], outbufL);

      FilterL->applyEffect(outbufR, outbufR2);
      FilterR->applyEffect(outbufL,outbufL2);

      ChorusL->applyEffect(outbufR2, outbuffer[2*x]);
      ChorusR->applyEffect(outbufL2, outbuffer[2*x+1]);
    }
    jack.writeSamples(outbuffer,chunksize*2);
  } while(running);

  return 0;
}
