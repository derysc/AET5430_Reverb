/*
  ==============================================================================

    Main_Component.cpp
    Created: 10 Nov 2025 12:51:19pm
    Author:  Derys

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Main_Component.h"

Main_Component::Main_Component(Belmont_ReverbAudioProcessor& p) : audioprocessor(p), m_pShared_Images(p.getSharedImages()), hitPads(m_pShared_Images), gainKnob(m_pShared_Images, p.apvts, "GainKnob")

{
    
    // Dropdown Menu
    menu.addItem("Echo Plate", 1);
    menu.addItem("A Plate", 2);
    menu.addItem("Jazz Hall", 3);
    menu.addItem("Large Church", 4);
    menu.addItem("Large Room" ,5);
    menu.addItem("Medium Hall", 6);
    menu.addItem("Small Hall", 7);
    menu.addItem("McAfee", 8);
    menu.addItem("MPAC", 9);
    menu.addItem("Classroom", 10);
    
    menu.setTextWhenNothingSelected("None");
    
    menu.onChange = [this]() {
        auto id = menu.getSelectedId();
        audioprocessor.setImpulseResponseFromID(id);
    };
    
    addAndMakeVisible(hitPads);
    addAndMakeVisible(gainKnob);
    
   // sliderAttachments.emplace_back(std::make_unique<SliderAttachment> (audioProcessor.apvts, "GainKnob", outGain));
 //   sliderAttachments.emplace_back(std::make_unique<SliderAttachment>(audioProcessor.apvts, "WetDryKnob", mixSlider));
    
//    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//    (audioprocessor.apvts, "GainKnob", gainKnob);
    
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
    (audioprocessor.apvts, "Bypass", hitPads);
    
    
    
}

Main_Component::~Main_Component()
{
}

void Main_Component::paint(juce::Graphics& g) {
    
    g.drawImage(m_pShared_Images->getBackground(), 0, 0, getWidth(), getHeight(), 0, 0, 2000, 1400);
    addAndMakeVisible(menu);
    menu.setBounds(120,40, 150, 30);
}

void Main_Component::resized()
{
    hitPads.setBounds(736, 28, 182, 210);
    gainKnob.setBounds(400, 400, 252, 252);
}
