/*
  ==============================================================================

    OutGain.h
    Created: 26 Apr 2025 1:34:51am
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include <cmath>

class OutGain
{
    public:
    
    float processSample(float x, int const channel);
    
    void setGain(float gain) {
        linGain = std::powf(10.f,gain/20.f);
    }
    
    private:
    
    float linGain = 1.f;
    
};
