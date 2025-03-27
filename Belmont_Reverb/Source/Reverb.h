/*
  ==============================================================================

    Reverb.h
    Created: 11 Mar 2025 7:05:36pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "AudioProcessor.h"

class Reverb : public AudioProcessor
{
    
    public:
    
    float proccesSample(float x, const int channel);
    
};
