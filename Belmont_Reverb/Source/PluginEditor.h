/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Belmont_ReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Belmont_ReverbAudioProcessorEditor (Belmont_ReverbAudioProcessor&);
    ~Belmont_ReverbAudioProcessorEditor() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    //using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
   // using BoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Belmont_ReverbAudioProcessor& audioProcessor;

    juce::ComboBox menu;
    juce::Slider mixSlider;
    juce::Slider outGain;
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    //std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
   // std::unique_ptr<BoxAttachment> irComboBoxAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Belmont_ReverbAudioProcessorEditor)
};
