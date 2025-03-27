/*
  ==============================================================================

    AudioEffect.h
    Created: 11 Mar 2025 6:47:37pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class AudioProcessor
{
    public:
    
    void prepare(double sampleRate);
    
    void processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSmaples);
    
    virtual float processSample(float x, const int channel) ;
    
    
    private:
    
    double Fs;
};
