/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Shared_Images.h"

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

    
    Shared_Images* getSharedImages()
    {return m_pShared_ImagesPtr;};
    
    float getOutputLevel() const { return outputLevel;}
    
    juce::AudioProcessorValueTreeState apvts;
    
    static constexpr int fftOrder = 11;       // 2048-point FFT
    static constexpr int fftSize  = 1 << fftOrder;

    juce::dsp::FFT fft { fftOrder };

    std::array<float, fftSize> fifo {};
    std::array<float, fftSize * 2> fftBuffer {};

    std::atomic<int> fifoIndex { 0 };
    std::atomic<bool> nextFFTBlockReady { false };
    
    void pushNextSampleIntoFifo(float sample);

    
    void IRChanged (float Ir){
        currentIR = Ir;
    }
    
private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    juce::SharedResourcePointer<Shared_Images> m_pShared_ImagesPtr;
    
    int currentIR;
    
    //DSP Effects
    
    std::atomic<float> outputLevel = 0.0f;
    
    juce::AudioParameterBool* bypassParam;
    
    juce::dsp::ProcessSpec spec;
    juce::dsp::Gain<float> gain;
    juce::dsp::DryWetMixer<float> mix;
    juce::dsp::Convolution reverb;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Belmont_ReverbAudioProcessor)
};
