/*
  ==============================================================================

    Wet_DryMix.cpp
    Created: 28 Apr 2025 5:23:17pm
    Author:  Derys

  ==============================================================================
*/

#include "Wet_DryMix.h"


float Wet_DryMix::processSample(float dry, float wet)
{
    float y;
    if (mix >= 0.f) {
        y = dry * (1.0f - mix) + wet * mix;
    }
    else {
        return 0;
    }
    return y;
    
};
