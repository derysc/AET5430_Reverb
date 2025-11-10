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
    
    
    
    private:
    
    juce::Image m_Background;
        
        

    
    
    
};
