#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
    , message("Workgroup not yet changed")
{
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

    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText(message, getLocalBounds(), Justification::centred, 1);
}

void PluginEditor::resized()
{
}

void PluginEditor::changeListenerCallback(ChangeBroadcaster*)
{
    message = String::formatted("Workgroup changed %d times", audioProcessor.getWorkgroupChangeCount());
    repaint();
}
