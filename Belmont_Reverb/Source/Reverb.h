/*
  ==============================================================================

    Reverb.h
    Created: 11 Mar 2025 7:05:36pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Reverb
{
    public:
    
    void prepare(double sampleRate , double samplesPerBlock, const int numChannels) ;
    
    float proccesSample(float x, const int channel);
    
    juce::dsp::ProcessSpec spec;
    juce::dsp::Convolution convolution;
    
    private:
    
//    juce::dsp::ProcessSpec spec;
//    juce::dsp::Convolution convolution;
    
};
