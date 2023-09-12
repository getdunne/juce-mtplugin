#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    processorAddress.setJustificationType(Justification::centred);
    addAndMakeVisible(processorAddress);
    
    changeCountMessage.setJustificationType(Justification::centred);
    addAndMakeVisible(changeCountMessage);
    
    setSize(500, 200);
    
    audioProcessor.addChangeListener(this);
    changeListenerCallback(nullptr);
}

PluginEditor::~PluginEditor()
{
    audioProcessor.removeChangeListener(this);
}

void PluginEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    processorAddress.setBounds(area.removeFromTop(24));
    area.removeFromTop(20);
    changeCountMessage.setBounds(area.removeFromTop(24));
}

void PluginEditor::changeListenerCallback(ChangeBroadcaster*)
{
    processorAddress.setText("Processor address 0x" + String::toHexString((uint64)&audioProcessor), dontSendNotification);
    changeCountMessage.setText(String::formatted("Workgroup changed %d times", audioProcessor.getWorkgroupChangeCount()), dontSendNotification);
}
