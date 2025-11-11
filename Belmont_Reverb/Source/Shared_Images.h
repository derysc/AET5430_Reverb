/*
  ==============================================================================

    Shared_Images.h
    Created: 10 Nov 2025 12:52:28pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Shared_Images {
    
public:
    
    Shared_Images() {
        loadImages();
    };
    
    void loadImages() ;
    
    juce::Image& getBackground() {
        return m_Background;
    };
    
    juce::Image& getPadButtonOn() {
        return m_PadButtonOn;
    };
    
    juce::Image& getPadButtonOff() {
        return m_PadButtonOff;
    };
    
    
    
    private:
    
    juce::Image m_Background;
    
    juce::Image m_PadButtonOn;
    
    juce::Image m_PadButtonOff;
        
    
};
