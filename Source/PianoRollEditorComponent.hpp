//
//  PianoRollEditorComponent.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 05/02/2020.
//

#ifndef PianoRollEditorComponent_hpp
#define PianoRollEditorComponent_hpp

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
        Viewport::visibleAreaChanged(newVisibleArea);
        if (positionMoved) {
            positionMoved(getViewPositionX(), getViewPositionY());
        }
    }
    
    std::function<void(int,int)> positionMoved;
};


/*
 
 |      |   timeline component
 |______|__________________________________________
 |      |
 |      |
 |keys  |   main viewport and note grid component
 |      |
 |      |
 |      |
 |      |
 |      |
 |      |
 |      |
 |      |
 |      |
 
 
 */

class PianoRollEditorComponent   : public Component
{
public:
    
    struct ExternalModelEditor {
        std::vector<NoteModel *> models; //const event pointers but mutable elements
        std::function<void()> update; //once you have made the edits then call this
    };
    
    //==============================================================================
    PianoRollEditorComponent();
    ~PianoRollEditorComponent();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void showControlPannel (bool state);
    void setStyleSheet (NoteGridStyleSheet style);
    void setup (const int bars, const int pixelsPerBar, const int noteHeight);
    void updateBars (const int newNumberOfBars);
    
    void loadSequence (PRESequence sequence);
    PRESequence getSequence ();
    
    void setScroll (double x, double y);
    
    void disableEditing (bool value);
    NoteGridControlPanel & getControlPannel ();
    
    ExternalModelEditor getSelectedNoteModels ();
    
    std::function<void()> onEdit;
    std::function<void(int note,int velocity)> sendChange;

private:
    //==============================================================================
    // Your private member variables go here...
    NoteGridStyleSheet      styleSheet;
    NoteGridComponent       noteGrid;
    CustomViewport          viewportGrid, viewportPiano, viewportTimeline;
    NoteGridControlPanel    noteGridPanel;
    TimelineComponent       timelineComp;
    KeyboardComponent       keyboardComp;
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif /* PianoRollEditorComponent_hpp */
