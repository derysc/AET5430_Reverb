/*
  ==============================================================================

    Main_Component.h
    Created: 10 Nov 2025 12:51:19pm
    Author:  Derys

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "Shared_Images.h"

class Main_Component : public juce::Component
{
    
public:
    Main_Component(Belmont_ReverbAudioProcessor&);
    ~Main_Component() override;
    
    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    Belmont_ReverbAudioProcessor& audioprocessor;
    Shared_Images* m_pShared_Images;
    
    
};

