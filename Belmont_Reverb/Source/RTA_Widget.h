/*
  ==============================================================================

    RTA_Widget.h
    Created: 13 Nov 2025 10:48:07pm
    Author:  Derys

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"

class RTAComponent : public juce::Component, private juce::Timer
{
public:
    RTAComponent(Belmont_ReverbAudioProcessor& p) : processor(p)
    {
        startTimerHz(30);
        smoothedMagnitudes.resize(processor.fftSize / 2, -80.0f);
    }

    void paint(juce::Graphics& g) override
    {
        auto bounds  = getLocalBounds().toFloat();
        auto width   = bounds.getWidth();
        auto height  = bounds.getHeight();

        // Background
        g.fillAll(juce::Colours::black);

        // --------------------------------------------------------------------
        //  GRID LINES
        // --------------------------------------------------------------------
        g.setColour(juce::Colours::white.withAlpha(0.15f));

        // ---- Horizontal dB lines ----
        std::vector<float> dBMarks = { 10.f, 0.f, -6.f, -12.f, -24.f, -36.f, -48.f, -60.f };

        for (auto dB : dBMarks)
        {
            float y = juce::jmap(dB, -60.f, 10.f, height, 0.f);  // updated min/max range
            g.drawLine(0, y, width, y, 1.0f);

            g.setColour(juce::Colours::white.withAlpha(0.6f));
            g.drawFittedText(juce::String(dB) + " dB",
                             2, y - 10, 40, 20,
                             juce::Justification::left, 1);

            g.setColour(juce::Colours::white.withAlpha(0.15f));
        }


        // ---- Vertical frequency lines (log scale) ----
        std::vector<float> freqMarks = { 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000 };

        auto freqToX = [&](float freq) -> float
        {
            float minF = 20.0f;
            float maxF = 20000.0f;
            float norm = std::log(freq / minF) / std::log(maxF / minF);
            return norm * width;
        };

        for (auto freq : freqMarks)
        {
            float x = freqToX(freq);
            g.drawLine(x, 0, x, height, 1.0f);

            g.setColour(juce::Colours::white.withAlpha(0.6f));
            g.drawFittedText((freq < 1000 ? juce::String(freq) + " Hz"
                                         : juce::String(freq / 1000, 1) + " kHz"),
                             x - 20, height - 20, 40, 20,
                             juce::Justification::centred, 1);
            g.setColour(juce::Colours::white.withAlpha(0.15f));
        }

        // --------------------------------------------------------------------
        //  SPECTRUM DRAWING
        // --------------------------------------------------------------------
        g.setColour(juce::Colours::white);

        juce::Path pth;
        pth.startNewSubPath(0, height);

        for (int i = 0; i < processor.fftSize / 2; ++i)
        {
            float dB = smoothedMagnitudes[i];

            float y = juce::jmap(dB, -60.f, 10.f, height, 0.f);

            // frequency index → log scale X position
            float freq = (float)i * (processor.getSampleRate() / processor.fftSize);
            float x = freqToX(freq);

            pth.lineTo(x, y);
        }

        g.strokePath(pth, juce::PathStrokeType(1.5f));
    }

private:
    
    std::vector<float> smoothedMagnitudes;
    float smoothingFactor = 0.2f;
    float fallSpeed = 0.05f;        // how fast the line falls when audio drops
    
    Belmont_ReverbAudioProcessor& processor;

    void timerCallback() override
    {
        if (processor.nextFFTBlockReady.load())
        {
            processor.fft.performFrequencyOnlyForwardTransform(
                processor.fftBuffer.data()
            );
            processor.nextFFTBlockReady.store(false);

            // ---- Apply smoothing per-bin ----
            for (int i = 0; i < processor.fftSize / 2; ++i)
            {
                float mag = processor.fftBuffer[i];
                float dB = juce::Decibels::gainToDecibels(mag / 40.0f, -80.0f);

                float& sm = smoothedMagnitudes[i];

                // Rising: smooth up
                if (dB > sm)
                    sm = sm + smoothingFactor * (dB - sm);

                // Falling: use fallSpeed
                else
                    sm = sm + fallSpeed * (dB - sm);
            }

            repaint();
        }
    }
};

