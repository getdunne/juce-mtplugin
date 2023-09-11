#pragma once
#include <JuceHeader.h>

class PluginProcessor   : public AudioProcessor
                        , public ChangeBroadcaster
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void audioWorkgroupContextChanged(const AudioWorkgroup& workgroup) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

    bool hasEditor() const override { return true; }
    juce::AudioProcessorEditor* createEditor() override;

    const String getName() const override { return "MTPlugin"; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override { return ""; }
    void changeProgramName(int index, const String& newName) override {}

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    // editor interface
    const int getWorkgroupChangeCount() { return workgroupChangeCount; }

private:
    int workgroupChangeCount;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
