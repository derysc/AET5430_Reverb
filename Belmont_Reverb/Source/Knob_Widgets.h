/*
  ==============================================================================

    Knob_Widgets.h
    Created: 11 Nov 2025 12:30:52am
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Shared_Images.h"

class MediumKnob : public juce::Slider
{
    public:
    
    MediumKnob (Shared_Images* i, juce::AudioProcessorValueTreeState& state, const juce::String& paramID)
    : knobImage(i->getMediumKnob())
    {
        setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
        setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        
        setRange(0.0f, 1.0f, 0.001f);
        
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                    state, paramID, *this);
    }
    
    ~MediumKnob() {};
    
    void paint(juce::Graphics& g) override
    {
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIdx = floor (fractRotation * (numFrames - 1));
        
        const int frameStartY = frameIdx * frameHeight;
        
        g.drawImage(knobImage, 0, 0, 150, 150 , 0, frameStartY, 252, frameHeight);
        
    }
    
    
    private:
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    
    juce::Image& knobImage;
    
    int numFrames = 129;
    
    int frameHeight = 252;
};
