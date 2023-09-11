# juce-mtplugin
This is a minimal JUCE 7 instrument plugin, for testing the new *audioWorkgroupContextChanged* functionality
added to *juce::AudioProcessor* on the JUCE 7.0.7 *develop* branch.

As of 2023-09-11, the code verifies that
1. With the latest JUCE update, this and other plug-ins can be compiled as Audio Unit (v2) and can be loaded into *Logic Pro X* 10.7.9 on *MacOS Ventura* 13.5.2, and will not crash.
2. Unfortunately, the *audioWorkgroupContextChanged* function does not appear to be called by *Logic* in this case.
