/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Belmont_ReverbAudioProcessorEditor::Belmont_ReverbAudioProcessorEditor (Belmont_ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    menu.addItem("Echo Plate", 1);
    menu.addItem("A Plate", 2);
    menu.addItem("Jazz Hall", 3);
    menu.addItem("Large Church", 4);
    menu.addItem("Large Room" ,5);
    menu.addItem("Medium Hall", 6);
    menu.addItem("Small Hall", 7);
    
    menu.onChange = [this]() {
        audioProcessor.setImpulseResponseFromID(menu.getSelectedId());
    };
}

Belmont_ReverbAudioProcessorEditor::~Belmont_ReverbAudioProcessorEditor()
{
}

//==============================================================================
void Belmont_ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colours::steelblue);

//    g.setColour (juce::Colours::white);
//    g.setFont (juce::FontOptions (15.0f));
//    g.drawte
    
    
    addAndMakeVisible(menu);
    menu.setBounds(200,100, 150, 30);
}

void Belmont_ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
