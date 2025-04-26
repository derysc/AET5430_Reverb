/*
  ==============================================================================

    OutGain.cpp
    Created: 26 Apr 2025 1:34:51am
    Author:  Derys

  ==============================================================================
*/

#include "OutGain.h"


float OutGain::processSample(float x, const int channel) {
    float y = x * linGain;
    return y;
};
