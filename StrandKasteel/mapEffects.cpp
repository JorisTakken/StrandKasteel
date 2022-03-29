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
#include "avaraging.h"

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
CentroidDetection detect;
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

float param1;
float param2;
float param3;
float param4;
float param5;
float param6;
float param7;
float param8;
float param9;
float param10;

float linMap(float input, float x1, float x2, float min, float max){
  // STARTING AT A X VALUE
    float value = (min * (x2 - input) + max * (input - x1)) / (x2 - x1);
    return value;
}


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

      outbuffer[2*x+1] = input;
      outbuffer[2*x] = input;

      ((TapeDelay*)TapeDelayR)->setDelayMS(param1);
      ((TapeDelay*)TapeDelayL)->setDelayMS(param1);
      ((TapeDelay*)TapeDelayR)->setFeedback(param2);
      ((TapeDelay*)TapeDelayL)->setFeedback(param2);
      ((TapeDelay*)TapeDelayR)->setDrive(param3);
      ((TapeDelay*)TapeDelayL)->setDrive(param3);
      ((TapeDelay*)TapeDelayR)->setModFreq(param4);
      ((TapeDelay*)TapeDelayL)->setModFreq(param4);
      ((Filter*)FilterR)->setCutoff(param5);
      ((Filter*)FilterL)->setCutoff(param5);
      ((Chorus*)ChorusL)->setModFreq(param6);
      ((Chorus*)ChorusR)->setModFreq(param6);
      ((Chorus*)ChorusL)->setModDepth(param7);
      ((Chorus*)ChorusR)->setModDepth(param7);
      ((Tremolo*)TremoloR)->setModFreq(param8);
      ((Tremolo*)TremoloL)->setModFreq(param8);
      ((Tremolo*)TremoloR)->setModDepht(param9);
      ((Tremolo*)TremoloL)->setModDepht(param9);

      FilterL->applyEffect(input, outbufR2);
      FilterR->applyEffect(input,outbufL2);

      ChorusL->applyEffect(outbufR2, outbufR3);
      ChorusR->applyEffect(outbufL2, outbufL3);

      TremoloR->applyEffect(outbufL3, outbufL4);
      TremoloL->applyEffect(outbufR3, outbufR4);

      TapeDelayL->applyEffect(outbufL4, outbuffer[2*x+1]);
      TapeDelayR->applyEffect(outbufR4, outbuffer[2*x]);
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
  jack.setNumberOfInputChannels(2);
  jack.setNumberOfOutputChannels(2);

  Avaraging average1;
  average1.setSmoothFactor(10);
  Avaraging average2;
  average2.setSmoothFactor(10);
  Avaraging average3;
  average3.setSmoothFactor(10);
  Avaraging average4;
  average4.setSmoothFactor(10);
  Avaraging average5;
  average5.setSmoothFactor(1000);
  Avaraging average6;
  average6.setSmoothFactor(10);
  Avaraging average7;
  average7.setSmoothFactor(10);
  Avaraging average8;
  average8.setSmoothFactor(10);
  Avaraging average9;
  average9.setSmoothFactor(10);
  Avaraging average10;
  average10.setSmoothFactor(10);

  thread filterThread(audio);

  while (running) {
    cap >> camera;
    detect.drawPoints(camera);
    detect.drawBigCentroid(camera);
    detect.listGen();
    imshow("Display window", camera);

    param1 = linMap(average1.smooth(detect.getParam1()),0, 2000, 0 ,1500); // tapedelay tijd
    param2 = linMap(average2.smooth(detect.getParam2()),0, 2000, 0 ,0.3); // tapedelay feedback
    param3 = linMap(average3.smooth(detect.getParam3()),0, 2000, 0 ,2); // tapedelay drive
    param4 = linMap(average4.smooth(detect.getParam4()),0, 2000, 0 ,10); // tapedelay modFreq
    param5 = linMap(average5.smooth(detect.getParam5()),0, 2000, 0.5 ,1); // filter cutoff
    param6 = linMap(average6.smooth(detect.getParam6()),0, 2000, 0 ,5); // chorus modFreq
    param7 = linMap(average7.smooth(detect.getParam7()),0, 2000, 0 ,1); // chorus modDepth
    param8 = linMap(average8.smooth(detect.getParam8()),0, 2000, 0 ,10); // tremolo modFreq
    param9 = linMap(average9.smooth(detect.getParam9()),0, 2000, 0 ,1); // tremolo modDepth
    param10 = linMap(average10.smooth(detect.getParam10()),0, 2000, 0 ,1); // overal drywet

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
