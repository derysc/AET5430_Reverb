/*
  ==============================================================================

    Meter_Widget.h
    Created: 13 Nov 2025 5:10:04pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "Shared_Images.h"


class SimpleMeter : public juce::Component, private juce::Timer
{
public:
    SimpleMeter(Belmont_ReverbAudioProcessor& p) : audioProcessor(p)
    {
        
        startTimerHz(30);
        
    }
    
    ~SimpleMeter(){}
    
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat().reduced(3.f);

        g.setColour(juce::Colours::black);
        g.fillRect(bounds);

        g.setGradientFill(gradient);
        const auto scaledY = juce::jmap(dbLevel, -60.f, 10.f, 0.f, static_cast<float>(getHeight()));
        g.fillRect(bounds.removeFromBottom(scaledY));
        
    }

    void resized() override
    {
        const auto bounds = getLocalBounds().toFloat();
        gradient = juce::ColourGradient{ juce::Colours::green, bounds.getBottomLeft(), juce::Colours::red, bounds.getTopLeft(), false };
        gradient.addColour(0.5, juce::Colours::yellow);
    }
    
    
    void timerCallback() override {
        
        updateMeter();

        repaint();
    }
    
    void updateMeter()
    {
        
        dbLevel = audioProcessor.getOutputLevel();
          
        repaint();
    }
    
    
    
private:
    Belmont_ReverbAudioProcessor& audioProcessor;
            
    juce::ColourGradient gradient{};
    
    float dbLevel = 0;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMeter)
};
