/*
  ==============================================================================

    Wet_DryMix.h
    Created: 28 Apr 2025 5:23:17pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Wet_DryMix
{
    
    public:
    
    void setMix(float newMix)
    {
        mix = newMix;
    }
    
    float getMix()
    {
        return mix;
    }
    
    float processSample(float dry, float wet);
    
    
    
    private:
    
    float mix = 1.f;
    
    
    
};
