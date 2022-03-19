#include "jack_module.h"
#include <string>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <iostream>

#include "chorus.h"
#include "filter.h"
#include "delay.h"
#include "waveshaper.h"
#include "tremolo.h"
#include "sine.h"
#include "tape_delay.h"

unsigned long chunksize = 256;
JackModule jack;
float samplerate = 44100;

enum effectChoice {chorus = 0, filter = 1, delay = 2, tapeDelay = 3, waveshaper = 4, tremolo = 5};

bool running = true;

int main(int argc, char **argv){


  jack.init(argv[0]);
  jack.autoConnect();

  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);

  float *inbuffer = new float[chunksize];
  float *outbuffer = new float[chunksize];

    effectChoice effect;
    effect = tapeDelay;

    Effect* effectL;
    Effect* effectR;
    switch (effect) {
      case effectChoice::chorus:
          effectL = new Chorus(1,1,100,0.0,samplerate);// modFreq, modDepth, delayMS, feedback, samplerate
          effectR = new Chorus(1,1,50,0.0,samplerate);
          break;
      case effectChoice::filter:
          effectL = new Filter(Filter::filterType::highpass,1,0); //filterType, cutoff, LFOrate
          effectR = new Filter(Filter::filterType::highpass,1,0);
          break;
      case effectChoice::delay:
          effectL = new Delay(samplerate,22050,0.5); // size, numSamplesDelay,  feedback
          effectR = new Delay(samplerate,22050,0.5);
          break;
      case effectChoice::tapeDelay:
          effectL = new TapeDelay(samplerate, 500, 0.4, 3, 2); // size, delayMS, feedback, modFreq, Drive
          effectR = new TapeDelay(samplerate, 500, 0.4, 3, 2);
          break;
      case effectChoice::waveshaper:
          effectL = new Waveshaper(1000); // int buffersize
          effectR = new Waveshaper(1000);
          // ((Waveshaper*)effectL)->genWaveshape(10.0);
          // ((Waveshaper*)effectR)->genWaveshape(10.0);
          ((Waveshaper*)effectL)->genWaveshapeOscillator(Waveshaper::WaveChoise::sine,10);
          ((Waveshaper*)effectR)->genWaveshapeOscillator(Waveshaper::WaveChoise::sine,10);
          // ((Waveshaper*)effectR)->plot_waveshaper();
          break;
      case effectChoice::tremolo:
          effectL = new Tremolo(Tremolo::Waveformtype::sine, 1, 1); // Tremolo::Waveformtype:sine, modFreq, modDepht
          effectR = new Tremolo(Tremolo::Waveformtype::sine, 1, 1);
          break;
    }
    effectL->setDrywet(1);
    effectR->setDrywet(1);


  do{
    jack.readSamples(inbuffer,chunksize);
    for(unsigned int x=0; x<chunksize; x++)
    {
      // ... your algorithm here
      effectL->applyEffect(inbuffer[x], outbuffer[2*x]);
      effectR->applyEffect(inbuffer[x], outbuffer[2*x+1]);
    }
    jack.writeSamples(outbuffer,chunksize*2);
  } while(running);

  return 0;
}
