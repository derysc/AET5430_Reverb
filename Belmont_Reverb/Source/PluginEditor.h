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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Belmont_ReverbAudioProcessorEditor)
};
