/*
  ==============================================================================

    Main_Component.cpp
    Created: 10 Nov 2025 12:51:19pm
    Author:  Derys

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Main_Component.h"

Main_Component::Main_Component(Belmont_ReverbAudioProcessor& p) : audioprocessor(p), m_pShared_Images(p.getSharedImages()), hitPads(m_pShared_Images), gainKnob(m_pShared_Images, p.apvts, "GainKnob" , "Gain"), mixKnob(m_pShared_Images, p.apvts, "MixKnob", "Dry/Wet Mix"),
    meter(audioprocessor)

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
    
    rta = std::make_unique<RTAComponent>(audioprocessor);
    addAndMakeVisible(*rta);
    
    addAndMakeVisible(hitPads);
    addAndMakeVisible(gainKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(menu);
    addAndMakeVisible(meter);
    
    
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
    (audioprocessor.apvts, "Bypass", hitPads);
    
    
    
}

Main_Component::~Main_Component()
{
}

void Main_Component::paint(juce::Graphics& g) {

    g.fillAll(juce::Colours::darkgrey);
    
}

void Main_Component::resized()
{
    menu.setBounds( 52 , 184 , 120 ,45);
    hitPads.setBounds(50, 25 , 125 , 177);
    gainKnob.setBounds( 780 , 250 , 252, 252);
    mixKnob.setBounds( 780 , 60 , 252, 252);
    meter.setBounds(100, 260 , 28 , 190);
    rta->setBounds(200, 77, 590 , 375 );
}
