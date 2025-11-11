/*
  ==============================================================================

    Button_Widgets.h
    Created: 10 Nov 2025 8:22:04pm
    Author:  Derys

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Shared_Images.h"

class HitPads : public juce::ImageButton
{
    public:
    
    HitPads(Shared_Images* i) : buttonEnabled(i->getPadButtonOn()), buttonDisabled(i->getPadButtonOff())
    {
        setClickingTogglesState(true);
        
        setImages(true, false, true, buttonDisabled, 1.f, juce::Colours::transparentWhite, buttonDisabled, 1.f, juce::Colours::transparentWhite, buttonEnabled, 1.f, juce::Colours::transparentWhite);
        
        setToggleState(false, juce::dontSendNotification);
    }
    
    ~HitPads() {};
    
    private:
    
    juce::Image& buttonEnabled, buttonDisabled;
    
};
