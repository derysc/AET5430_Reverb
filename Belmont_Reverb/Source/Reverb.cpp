/*
  ==============================================================================

    Reverb.cpp
    Created: 11 Mar 2025 7:05:36pm
    Author:  Derys

  ==============================================================================
*/

#include "Reverb.h"


void Reverb::prepare(double sampleRate, double samplesPerBlock, const int numChannels)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = numChannels;
    convolution.prepare(spec);
    
}

float Reverb::proccesSample(float x, const int channel) {
    return x;
}



