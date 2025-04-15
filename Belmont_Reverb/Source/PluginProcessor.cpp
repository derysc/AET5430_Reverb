/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Belmont_ReverbAudioProcessor::Belmont_ReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Belmont_ReverbAudioProcessor::~Belmont_ReverbAudioProcessor()
{
}

//==============================================================================
const juce::String Belmont_ReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Belmont_ReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Belmont_ReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Belmont_ReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Belmont_ReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Belmont_ReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Belmont_ReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Belmont_ReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Belmont_ReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void Belmont_ReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Belmont_ReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    convolution.prepare(spec);
    
   // auto irFile = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getChildFile("Large Church.aif");
    
//    if( irFile.existsAsFile())
//    {
//        convolution.loadImpulseResponse(irFile, juce::dsp::Convolution::Stereo::yes,
//                                        juce::dsp::Convolution::Trim::yes, 0);
//    }
//    else
//    {
//        DBG("IR file not found: " + irFile.getFullPathName());
//    }
//
    
}

void Belmont_ReverbAudioProcessor::releaseResources()
{
    convolution.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Belmont_ReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

   #endif

    return true;
#endif
}
#endif

void Belmont_ReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //dry buffer
    juce::AudioBuffer<float> dryBuffer;
    dryBuffer.makeCopyOf(buffer);
    
    //wet buffer processing
    juce::dsp::AudioBlock <float> block (buffer);
    if (convolution.getCurrentIRSize() > 0 ) {
        convolution.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    
    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        
        auto* dry = dryBuffer.getReadPointer(channel);
        auto* wet = buffer.getWritePointer(channel);
        
        
        for (int n = 0; n < buffer.getNumSamples() ; ++n) {
            
            if (dryWetMix >= 0.0f) {
                wet[n] = dry[n] * (1.0f - dryWetMix) + wet[n] * dryWetMix;
            } 
            
        };
    }
}

//==============================================================================
bool Belmont_ReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Belmont_ReverbAudioProcessor::createEditor()
{
    return new Belmont_ReverbAudioProcessorEditor (*this);
}

//==============================================================================
void Belmont_ReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Belmont_ReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Belmont_ReverbAudioProcessor::setImpulseResponseFromID(int id) {
    
    convolution.reset();
    
    switch (id)
    {
            
        case 1: // Echo Plate
            convolution.loadImpulseResponse(BinaryData::Echo_Plate_aif, BinaryData::Echo_Plate_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
         
        case 2: // A Plate
            convolution.loadImpulseResponse(BinaryData::A_Plate_aif, BinaryData::A_Plate_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        case 3: // Jazz Hall
            convolution.loadImpulseResponse(BinaryData::Jazz_Hall_aif, BinaryData::Jazz_Hall_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        case 4: // Large Church
            convolution.loadImpulseResponse(BinaryData::Large_Church_aif, BinaryData::Large_Church_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        case 5: // Large Room
            convolution.loadImpulseResponse(BinaryData::Large_Room_aif, BinaryData::Large_Room_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        case 6: // Medium Hall
            convolution.loadImpulseResponse(BinaryData::Medium_Hall_aif, BinaryData::Medium_Hall_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        case 7: // Small Hall
            convolution.loadImpulseResponse(BinaryData::Small_Hall_aif, BinaryData::Small_Hall_aifSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes,0);
        
        break;
            
        default:
                    DBG("Invalid IR ID");
        break;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Belmont_ReverbAudioProcessor();
}
