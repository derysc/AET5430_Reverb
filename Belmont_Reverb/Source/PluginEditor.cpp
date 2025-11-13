/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Belmont_ReverbAudioProcessorEditor::Belmont_ReverbAudioProcessorEditor (Belmont_ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), main_componet(p)
{
    
    setSize (1000, 500);
    
    addAndMakeVisible(main_componet);
    
}

Belmont_ReverbAudioProcessorEditor::~Belmont_ReverbAudioProcessorEditor()
{
}

//==============================================================================
void Belmont_ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void Belmont_ReverbAudioProcessorEditor::resized()
{
    main_componet.setBounds(0, 0, 1000, 500);
}
