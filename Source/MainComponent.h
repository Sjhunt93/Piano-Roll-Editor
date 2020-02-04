/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteGridControlPanel.hpp"
#include "TimelineComponent.hpp"
#include "KeyboardComponent.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class CustomViewport : public Viewport
{
public:
    void visibleAreaChanged (const Rectangle<int>& newVisibleArea)
    {
        std::cout << "Area scrolled: " << getViewPositionX() << " - " << getViewPositionY() << "\n";
        Viewport::visibleAreaChanged(newVisibleArea);
        if (positionMoved) {
            positionMoved(getViewPositionX(), getViewPositionY());
        }
    }

    std::function<void(int,int)> positionMoved;
};

class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    NoteGridStyleSheet      styleSheet;
    NoteGridComponent       noteGrid;
    CustomViewport          viewportGrid, viewportPiano, viewportTimeline;
    NoteGridControlPanel    noteGridPanel;
    TimelineComponent       timelineComp;
    KeyboardComponent       keyboardComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};