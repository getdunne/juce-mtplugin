#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class PluginEditor  : public AudioProcessorEditor
                    , public ChangeListener
{
public:
    PluginEditor(PluginProcessor&);
    ~PluginEditor() override;

    // Component
    void paint(Graphics&) override;
    void resized() override;
    
    // ChangeListener
    void changeListenerCallback(ChangeBroadcaster*) override;

private:
    PluginProcessor& audioProcessor;
    
    Label processorAddress, changeCountMessage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
