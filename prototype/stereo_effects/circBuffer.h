#pragma once
#include <iostream>

class CircBuffer{
	public:
		CircBuffer(int size, int numSamplesDelay);
		~CircBuffer();

		void setDelaySamps(float numSamplesDelay);
		void write(float sample);
		float read();
		float readNext();

		

	private:
		int wrap(int head);
		unsigned int readIndex;
		unsigned int writeIndex;
		unsigned int size;
		int numSamplesDelay;
		float* buffer = nullptr;

};