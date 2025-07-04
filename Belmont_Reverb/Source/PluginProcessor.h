/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OutGain.h"
#include "Reverb.h"
#include "Wet_DryMix.h"

//==============================================================================
/**
*/
class Belmont_ReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Belmont_ReverbAudioProcessor();
    ~Belmont_ReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    void setImpulseResponseFromID(int id);

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

   // float dryWetMix = 1.f; // 100%
    //float outGain = 1.f;
    
    juce::AudioProcessorValueTreeState apvts;
    
    void GainKnobChanged (float newGain){
        gainKnobValue.store(newGain);
    };
    
    void WetDryChanged (float value) {
        WetDryValue.store(value);
    };
    
    void IRChanged (float Ir){
        currentIR = Ir;
    }
    
private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    std::atomic<float> gainKnobValue;
    
    std::atomic<float> WetDryValue;
    
    int currentIR;
    
    OutGain gain;
    Reverb reverb;
    Wet_DryMix wetDryMix;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Belmont_ReverbAudioProcessor)
};
