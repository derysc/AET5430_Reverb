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
    
}
