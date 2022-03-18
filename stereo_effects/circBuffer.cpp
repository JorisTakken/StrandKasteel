#include "circBuffer.h"

CircBuffer::CircBuffer(int size, int numSamplesDelay) : readIndex(0), writeIndex(0){
  this -> size = size;
  this -> numSamplesDelay = numSamplesDelay;
  buffer = new float [size];
  setDelaySamps(numSamplesDelay);
}

CircBuffer::~CircBuffer(){
  delete [] buffer;
  buffer = nullptr;
}

void CircBuffer::setDelaySamps(float numSamplesDelay){
  // std::cout << "CircularBuffer - setReadIndex - numSamplesDelay = " << numSamplesDelay << std::endl;
  readIndex = writeIndex - numSamplesDelay + size;
  readIndex = wrap(readIndex);
  // std::cout << "CircularBuffer - setReadIndex - readIndex = " << readIndex << std::endl;
  // std::cout << "CircularBuffer - setReadIndex - writeIndex = " << writeIndex << std::endl;
  // readIndex = writeIndex - numSamplesDelay
}

void CircBuffer::write(float sample){
  buffer[writeIndex++] = sample;
  writeIndex = wrap(writeIndex);
}

float CircBuffer::read(){
  float sample = buffer[readIndex++];
  readIndex = wrap(readIndex);
  return sample;
}

float CircBuffer::readNext(){
  int readNext = readIndex + 1;
  float sample = buffer[readNext++];
  readIndex = wrap(readIndex);
  return sample;
}

int CircBuffer::wrap(int head){
  if(head>=size) head -=size;
  return head;
}

