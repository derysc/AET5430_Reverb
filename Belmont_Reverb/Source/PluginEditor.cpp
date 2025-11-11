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
    
    setSize (1000, 700);
    
    addAndMakeVisible(main_componet);
    
    //irComboBoxAttachment = std::make_unique<BoxAttachment>(audioProcessor.apvts,"IRMenu", menu );
   
    
//============================================================
    
    //Dry/Wey slider code
    
//    mixSlider.setRange(0, 1);
//    mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//    
//    mixSlider.onValueChange = [this]() {
//        audioProcessor.WetDryChanged(mixSlider.getValue());
//    };
//    
//    mixSlider.setValue(1.f);
//    
    
//============================================================
    
    //outgain knob
    
//    outGain.setRange(0, 3);
//    outGain.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//    
//    outGain.onValueChange = [this]() {
//        audioProcessor.GainKnobChanged(outGain.getValue());
//    };
    
   // outGain.setValue(1.f);
    
    
//    sliderAttachments.emplace_back(std::make_unique<SliderAttachment> (audioProcessor.apvts, "GainKnob", outGain));
//    
//    sliderAttachments.emplace_back(std::make_unique<SliderAttachment>(audioProcessor.apvts, "WetDryKnob", mixSlider));
//    
//    
//    
    
}

Belmont_ReverbAudioProcessorEditor::~Belmont_ReverbAudioProcessorEditor()
{
}

//==============================================================================
void Belmont_ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    
//    g.fillAll (juce::Colours::steelblue);
//
//    g.setColour (juce::Colours::black);
//    g.setFont (juce::FontOptions (20.f));
//    g.drawSingleLineText("Dry/Wet", 487,209);
//    g.drawSingleLineText("Program:",40,60 );
//    g.drawSingleLineText("OutGain", 487, 60);
//    
//    addAndMakeVisible(mixSlider);
//    mixSlider.setBounds(380, 118, 200,300);
//    
//    addAndMakeVisible(outGain);
//    outGain.setBounds(380,-20, 200, 300);
    
}

void Belmont_ReverbAudioProcessorEditor::resized()
{
    main_componet.setBounds(0, 0, getWidth(), getHeight());
}
