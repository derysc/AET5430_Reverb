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
    
    //irComboBoxAttachment = std::make_unique<BoxAttachment>(audioProcessor.apvts,"IRMenu", menu );
    
    
    
    
//============================================================
    
    //Dry/Wey slider code
    
    mixSlider.setRange(0, 1);
    mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    
    mixSlider.onValueChange = [this]() {
        audioProcessor.WetDryChanged(mixSlider.getValue());
    };
    
   // mixSlider.setValue(1.f);
    
    
//============================================================
    
    //outgain knob
    
    outGain.setRange(0, 3);
    outGain.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    
    outGain.onValueChange = [this]() {
        audioProcessor.GainKnobChanged(outGain.getValue());
    };
    
   // outGain.setValue(1.f);
    
    
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment> (audioProcessor.apvts, "GainKnob", outGain));
    
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment>(audioProcessor.apvts, "WetDryKnob", mixSlider));
    
    
    
    
}

Belmont_ReverbAudioProcessorEditor::~Belmont_ReverbAudioProcessorEditor()
{
}

//==============================================================================
void Belmont_ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colours::steelblue);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (20.f));
    g.drawSingleLineText("Dry/Wet", 487,209);
    g.drawSingleLineText("Program:",40,60 );
    g.drawSingleLineText("OutGain", 487, 60);
    
    
    
    addAndMakeVisible(menu);
    menu.setBounds(120,40, 150, 30);
    
    
    addAndMakeVisible(mixSlider);
    mixSlider.setBounds(380, 118, 200,300);
    
    addAndMakeVisible(outGain);
    outGain.setBounds(380,-20, 200, 300);
    
}

void Belmont_ReverbAudioProcessorEditor::resized()
{
    
}
