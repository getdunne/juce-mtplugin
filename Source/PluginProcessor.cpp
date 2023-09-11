#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true))
    , workgroupChangeCount(0)
{
}

PluginProcessor::~PluginProcessor()
{
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if ((layouts.getMainInputChannelSet() != AudioChannelSet::disabled())
        || (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()))
        return false;
    return true;
}

void PluginProcessor::audioWorkgroupContextChanged(const AudioWorkgroup& workgroup)
{
    ++workgroupChangeCount;
    sendChangeMessage();
}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    midiMessages.clear();
}

void PluginProcessor::getStateInformation(MemoryBlock& destData)
{
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

// Create new plugin editor
juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}
