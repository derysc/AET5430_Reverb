/*
  ==============================================================================

    AudioEffect.cpp
    Created: 11 Mar 2025 6:47:37pm
    Author:  Derys

  ==============================================================================
*/

#include "AudioProcessor.h"


void AudioProcessor::prepare(double sampleRate) {
    Fs = sampleRate;
}

void AudioProcessor::processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples) {
    for (int n = 0 ; n < numSamples ; ++n){
        float x = buffer.getSample(channel,n); // current sample
        float y = processSample(x,channel);
        buffer.setSample(channel,n,y);
    }
}
    
float AudioProcessor::processSample(float x, const int channel) {
    return x;
}
