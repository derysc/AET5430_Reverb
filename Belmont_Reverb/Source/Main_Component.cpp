/*
  ==============================================================================

    Main_Component.cpp
    Created: 10 Nov 2025 12:51:19pm
    Author:  Derys

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Main_Component.h"

Main_Component::Main_Component(Belmont_ReverbAudioProcessor& p) : audioprocessor(p), m_pShared_Images(p.getSharedImages())

{
    
};

Main_Component::~Main_Component()
{
}

void Main_Component::paint(juce::Graphics& g) {
    
    g.drawImage(m_pShared_Images->getBackground(), 0, 0, getWidth(), getHeight(), 0, 0, 2000, 1400);
}

void Main_Component::resized()
{
    
}
