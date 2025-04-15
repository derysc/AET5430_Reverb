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
    
    setSize (600, 400);
    
    //Dropdown menu code
    menu.addItem("Echo Plate", 1);
    menu.addItem("A Plate", 2);
    menu.addItem("Jazz Hall", 3);
    menu.addItem("Large Church", 4);
    menu.addItem("Large Room" ,5);
    menu.addItem("Medium Hall", 6);
    menu.addItem("Small Hall", 7);
    
    menu.setTextWhenNothingSelected("None");
    
    menu.onChange = [this]() {
        auto id = menu.getSelectedId();
        audioProcessor.setImpulseResponseFromID(id);
    };
    
//============================================================
    
    //Dry/Wey slider code
    
    mixSlider.setRange(0, 1);
    mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    
    mixSlider.onValueChange = [this]() {
        audioProcessor.dryWetMix = (float) mixSlider.getValue();
    };
    
    
//    mixSlider.setValue(0.5f, juce::dontSendNotification);
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
    addAndMakeVisible(mixSlider);
    mixSlider.setBounds(380, 118, 200,300);
    
}

void Belmont_ReverbAudioProcessorEditor::resized()
{
    
}
