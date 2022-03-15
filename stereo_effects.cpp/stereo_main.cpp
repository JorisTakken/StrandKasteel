#include "jack_module.h"
#include <string>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "chorus.h"
#include "sine.h"

unsigned long chunksize = 2048;
JackModule jack;
float samplerate = 44100;
Chorus chorusL(samplerate, 1, 0, 3); //samplerate,moddepth,feedback,modSpeed
Chorus chorusR(samplerate, 1, 0, 7);
bool running = true;

int main(int argc, char **argv){
  jack.init(argv[0]);
  jack.autoConnect();

  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);

  float *inbuffer = new float[chunksize];
  float *outbuffer = new float[chunksize];

  do{
    jack.readSamples(inbuffer,chunksize);
    for(unsigned int x=0; x<chunksize; x++)
    {
      // ... your algorithm here
      chorusL.processFrame(inbuffer[x], outbuffer[2*x]);
      chorusR.processFrame(inbuffer[x], outbuffer[2*x+1]);
    }
    jack.writeSamples(outbuffer,chunksize*2);
  } while(running);

  return 0;
}
