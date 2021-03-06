#include <string>
#include <iostream>
#include <math.h>
#include <thread>
#include <unistd.h> // sleep
#include "jack_module.h"
#include "keypress.h"
#include "bufferDebugger.h"

#include "chorus.h"
#include "filter.h"
#include "tremolo.h"
#include "sine.h"
#include "tape_delay.h"

unsigned long chunksize = 256;
JackModule jack;
float samplerate = 44100;

using namespace std;

bool running = true;


    Effect* TapeDelayL = new TapeDelay(samplerate, 500, 0.2, 3, 0); // size, delayMS, feedback, modFreq, Drive
    Effect* TapeDelayR = new TapeDelay(samplerate, 500, 0.2, 3, 0);

    Effect* FilterL = new Filter(Filter::filterType::lowpass,1,0); //filterType, cutoff, LFOrate
    Effect* FilterR = new Filter(Filter::filterType::lowpass,1,0);

    Effect* ChorusL = new Chorus(1,1,50,0.0,samplerate);// modFreq, modDepth, delayMS, feedback, samplerate
    Effect* ChorusR = new Chorus(1,1,50,0.0,samplerate);

    Effect* TremoloL = new Tremolo(Tremolo::Waveformtype::sine, 1,0.2);// waveform,  modFreq, modDepht
    Effect* TremoloR = new Tremolo(Tremolo::Waveformtype::sine, 1,0.2);



static void filter(float DWtrem){
    float *inbuffer = new float[chunksize];
    float *outbuffer = new float[chunksize];

    FilterL->setDrywet(1);
    ChorusL->setDrywet(1);
    TremoloL->setDrywet(0);

    TapeDelayR->setDrywet(0);
    TapeDelayL->setDrywet(0);


    FilterR->setDrywet(1);
    ChorusR->setDrywet(1);
    TremoloR->setDrywet(0);



    float outbufR;
    float outbufR2;
    float outbufR3;

    float outbufL;
    float outbufL2;
    float outbufL3;

  do{
    jack.readSamples(inbuffer,chunksize);
    for(unsigned int x=0; x<chunksize; x++){


      TapeDelayL->setDrywet(DWtrem);
      TapeDelayR->setDrywet(DWtrem);


      TapeDelayL->applyEffect(inbuffer[x], outbufR);
      TapeDelayR->applyEffect(inbuffer[x], outbufL);

      FilterL->applyEffect(outbufR, outbufR2);
      FilterR->applyEffect(outbufL,outbufL2);

      ChorusL->applyEffect(outbufR2, outbufR3);
      ChorusR->applyEffect(outbufL2, outbufL3);

      TremoloL->applyEffect(outbufR3, outbuffer[2*x]);
      TremoloR->applyEffect(outbufL3, outbuffer[2*x+1]);

    }


    jack.writeSamples(outbuffer,chunksize*2);
  } while(running);


    // delete TapeDelayL;
    // delete TapeDelayR;
    // delete FilterL;
    // delete FilterR;
    // delete ChorusL;
    // delete ChorusR;
    // delete TremoloL;
    // delete TremoloR;
    // TapeDelayL = nullptr;
    // TapeDelayR = nullptr;
    // FilterL = nullptr;
    // FilterR = nullptr;
    // ChorusL = nullptr;
    // ChorusR = nullptr;
    // TremoloR = nullptr;
    // TremoloL = nullptr;
    
  

}

int main(int argc, char **argv){
  char command='@';
  jack.init(argv[0]);
  jack.autoConnect();
  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);


  float newTremoloDryWet;

  std::thread filterThread(filter,newTremoloDryWet);




  while(command != 'q')
  {
    if(keypressed()) {
      command = getchar();

      if(command == '+' || command == '=') {
        newTremoloDryWet += 0.1;
        TapeDelayR->setDrywet(newTremoloDryWet);

        cout << newTremoloDryWet << endl;

      };
      if(command == '-'){
        std::cout << "je hebt geklikt baas" << std::endl;
      };
    }
    usleep(100000);
  }

  running=false;
  filterThread.join();

  jack.end();

  return 0;
}
