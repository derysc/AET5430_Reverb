/*
  ==============================================================================

    Shared_Images.cpp
    Created: 10 Nov 2025 12:52:28pm
    Author:  Derys

  ==============================================================================
*/

#include "Shared_Images.h"

void Shared_Images::loadImages() {
    
    m_Background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    m_PadButtonOn = juce::ImageCache::getFromMemory(BinaryData::Button_en_3_png, BinaryData::Button_en_3_pngSize);
    
    m_PadButtonOff = juce::ImageCache::getFromMemory(BinaryData::Button_dis_3_png, BinaryData::Button_dis_3_pngSize);
    
    m_MediumKnob = juce::ImageCache::getFromMemory(BinaryData::Knob_middle_png, BinaryData::Knob_middle_pngSize);
    
}
