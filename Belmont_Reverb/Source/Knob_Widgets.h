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
    
    MediumKnob (Shared_Images* i, juce::AudioProcessorValueTreeState& state, const juce::String& paramID, const juce::String& label)
    : knobImage(i->getMediumKnob()) , knobScale(i->getMediumKnobScale()), knobLabel(label)
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
        
        auto bounds = getLocalBounds().toFloat(); // full bounds of the slider
        
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIdx = floor (fractRotation * (numFrames - 1));
        
        const int frameStartY = frameIdx * frameHeight;
        
//        g.drawImage(knobImage, 0, 0, 150, 150 , 0, frameStartY, 252, frameHeight );
        float scaleFactor = 0.6; // your scaling factor (0.5 = half size, 1.0 = full size)

            float scaledWidth  = bounds.getWidth() * scaleFactor;
            float scaledHeight = bounds.getHeight() * scaleFactor;

            // Center them in the component
            float xOffset = (bounds.getWidth() - scaledWidth) / 2.0f;
            float yOffset = (bounds.getHeight() - scaledHeight) / 2.0f;

            // Draw scale first (background)
            g.drawImage(knobScale, 48 , 30 , scaledWidth, scaledHeight,   // target rect
                        0, 0, knobScale.getWidth(), knobScale.getHeight());

            // Draw knob on top
            g.drawImage(knobImage,
                        xOffset, yOffset, scaledWidth, scaledHeight,
                        0, frameStartY, knobImage.getWidth(), frameHeight);
        
        g.setColour(juce::Colours::white);
            g.setFont(17.f);
            
            juce::String labelText = knobLabel; // e.g., "Gain" or "Wet/Dry"
            float labelHeight = 20.0f;
            
            g.drawFittedText(labelText,0,171,  // 4 px padding below knob
                             getWidth(),
                             labelHeight,
                             juce::Justification::centred,
                             1);
        
    }
    
    private:
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    
    juce::String knobLabel;
    
    juce::Image& knobImage;
    
    juce::Image& knobScale;
    
    int numFrames = 129;
    
    int frameHeight = 252;
};
