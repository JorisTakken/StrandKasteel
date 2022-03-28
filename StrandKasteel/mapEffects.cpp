#include <string>
#include <iostream>
#include <math.h>
#include <thread>
#include <unistd.h> // sleep
#include "jack_module.h"
#include "keypress.h"
#include "bufferDebugger.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "centroidDetection.h"
#include "chorus.h"
#include "filter.h"
#include "tremolo.h"
#include "sine.h"
#include "tape_delay.h"

#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

using namespace cv;
using namespace std;
typedef unsigned int uint;

// camera capture
VideoCapture cap(0);
Mat camera;

// for audio
unsigned long chunksize = 256;
JackModule jack;
float samplerate = 44100;
bool running = true;

// make effects
// -------------------------------------------------------------------------------------------------------
Effect* TapeDelayL = new TapeDelay(samplerate, 500, 0.3, 1, 1); // size, delayMS, feedback, modFreq, Drive
Effect* TapeDelayR = new TapeDelay(samplerate, 500, 0.3, 1, 1);

Effect* FilterL = new Filter(Filter::filterType::highpass,1,0); //filterType, cutoff, LFOrate
Effect* FilterR = new Filter(Filter::filterType::lowpass,1,0);

Effect* ChorusL = new Chorus(1,1,50,0.0,samplerate);// modFreq, modDepth, delayMS, feedback, samplerate
Effect* ChorusR = new Chorus(1,1,50,0.0,samplerate);

Effect* TremoloL = new Tremolo(Tremolo::Waveformtype::sine, 1,1);// waveform,  modFreq, modDepht
Effect* TremoloR = new Tremolo(Tremolo::Waveformtype::sine, 1,1);
// -------------------------------------------------------------------------------------------------------


static void audio(){
  float inbuffer[chunksize];
  float outbuffer[chunksize * 2];

  float outbufR;
  float outbufR2;
  float outbufR3;
  float outbufR4;

  float outbufL;
  float outbufL2;
  float outbufL3;
  float outbufL4;

  TapeDelayL->setDrywet(1);
  FilterL->setDrywet(1);
  ChorusL->setDrywet(1);
  TremoloL->setDrywet(1);

  TapeDelayR->setDrywet(1);
  FilterR->setDrywet(1);
  ChorusR->setDrywet(1);
  TremoloR->setDrywet(1);

  do{
    jack.readSamples(inbuffer,chunksize);
    for(unsigned int x=0; x<chunksize; x++){
      float input = inbuffer[x];


      FilterL->applyEffect(input, outbufR2);
      FilterR->applyEffect(input,outbufL2);

      ChorusL->applyEffect(outbufR2, outbufR3);
      ChorusR->applyEffect(outbufL2, outbufL3);

      TremoloR->applyEffect(outbufL3, outbuffer[2*x+1]);
      TremoloL->applyEffect(outbufR3, outbuffer[2*x]);

      // TapeDelayL->applyEffect(outbufL4, outbuffer[2*x+1]);
      // TapeDelayR->applyEffect(outbufR4, outbuffer[2*x]);
    }

    jack.writeSamples(outbuffer,chunksize*2);
  } while(running);
    delete TapeDelayL;
    delete TapeDelayR;
    delete FilterL;
    delete FilterR;
    delete ChorusL;
    delete ChorusR;
    delete TremoloL;
    delete TremoloR;
    TapeDelayL = nullptr;
    TapeDelayR = nullptr;
    FilterL = nullptr;
    FilterR = nullptr;
    ChorusL = nullptr;
    ChorusR = nullptr;
    TremoloR = nullptr;
    TremoloL = nullptr;
}

int main(int argc, char **argv){
  char command='@';
  jack.init(argv[0]);
  jack.autoConnect();
  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);

  thread filterThread(audio);

  CentroidDetection detect;
  while (running) {
    cap >> camera;
    detect.drawPoints(camera);
    detect.drawBigCentroid(camera);
    detect.listGen();
    imshow("Display window", camera);
    waitKey(250);
  }

  while(command != 'q')
  {
    if(keypressed()) {
      command = getchar();
    }
    usleep(100000);
  }

  running=false;
  filterThread.join();
  cap.release();

  jack.end();
}
