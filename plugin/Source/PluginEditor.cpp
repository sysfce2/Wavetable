#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WavetableAudioProcessorEditor::WavetableAudioProcessorEditor (WavetableAudioProcessor& p)
    : ProcessorEditor (p), vaProc (p)
{
    scope.setName ("scope");
    scope.setNumChannels (2);
    scope.setTriggerMode (gin::TriggeredScope::TriggerMode::Up);
    scope.setColour (gin::TriggeredScope::traceColourId + 0, findColour(gin::PluginLookAndFeel::accentColourId, true).withAlpha (0.7f));
    scope.setColour (gin::TriggeredScope::traceColourId + 1, findColour(gin::PluginLookAndFeel::accentColourId, true).withAlpha (0.7f));
    scope.setColour (gin::TriggeredScope::lineColourId, juce::Colours::transparentBlack);

    addAndMakeVisible (editor);
    addAndMakeVisible (scope);
    scope.setBounds (674, 5, 177, 30);

    setSize (901, 671);
}

WavetableAudioProcessorEditor::~WavetableAudioProcessorEditor()
{
}

//==============================================================================
void WavetableAudioProcessorEditor::showAboutInfo()
{
   #if JUCE_DEBUG
    if (inspector == nullptr)
    {
        inspector = std::make_unique<melatonin::Inspector> (*this);
        inspector->setVisible(true);
    }
    else
    {
        inspector = nullptr;
    }
   #else
    ProcessorEditor::showAboutInfo();
   #endif
}

void WavetableAudioProcessorEditor::paint (juce::Graphics& g)
{
    ProcessorEditor::paint (g);

    titleBar.setShowBrowser (true);

    g.fillAll (findColour (gin::PluginLookAndFeel::blackColourId));
}

void WavetableAudioProcessorEditor::resized()
{
    ProcessorEditor::resized ();

    auto rc = getLocalBounds().reduced (1);
    rc.removeFromTop (40);

    editor.setBounds (rc);
    patchBrowser.setBounds (rc);
}
