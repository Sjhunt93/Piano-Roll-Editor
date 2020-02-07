//
//  PianoRollEditorComponent.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 05/02/2020.
//

#include "PianoRollEditorComponent.hpp"


//==============================================================================
PianoRollEditorComponent::PianoRollEditorComponent() : noteGrid(styleSheet), noteGridPanel(noteGrid, styleSheet)
{
 
    
    addAndMakeVisible(viewportGrid);
 
    viewportGrid.setViewedComponent(&noteGrid, false);
    viewportGrid.setScrollBarsShown(true, true);
    viewportGrid.setScrollBarThickness(10);
 
    addAndMakeVisible(noteGridPanel);
    
    viewportTimeline.setViewedComponent(&timelineComp, false);
    viewportTimeline.setScrollBarsShown(false, false);
    addAndMakeVisible(viewportTimeline);
    
    viewportPiano.setViewedComponent(&keyboardComp, false);
    viewportPiano.setScrollBarsShown(false, false);
    addAndMakeVisible(viewportPiano);
    
    viewportGrid.positionMoved = [this](int x, int y)
    {
        viewportTimeline.setViewPosition(x, y);
        viewportPiano.setViewPosition(x, y);
    };
    
    noteGridPanel.configureGrid = [this](int pixelsPerBar, int noteHeight)
    {
        setup(10, pixelsPerBar, noteHeight);
    };
    
    
//    setup(10, <#const int pixelsPerBar#>, <#const int noteHeight#>)
    
#if 0 //some test code for setting the notes on the grid
    
    Sequence seq;
    for (int i = 0; i < 16; i++) {
        NoteModel nm;
        nm.note = arc4random() % 24 + 48;
        nm.velocity = arc4random() % 50 + 55;
        nm.startTime = i * 240;
        nm.noteLegnth = 480;
        seq.events.push_back(nm);
    }
    noteGrid.loadSequence(seq);
#endif
}

PianoRollEditorComponent::~PianoRollEditorComponent()
{
    
}

//==============================================================================
void PianoRollEditorComponent::paint (Graphics& g)
{
//    g.fillAll(Colours::darkslateblue);
       g.fillAll(Colours::darkgrey.darker());
}

void PianoRollEditorComponent::resized()
{
    viewportGrid.setBounds(80, 50, getWidth()-90, noteGridPanel.isVisible() ? getHeight()-180 : getHeight() - 55);
    viewportTimeline.setBounds(viewportGrid.getX(), 5, viewportGrid.getWidth()-10, viewportGrid.getY() - 5);
    viewportPiano.setBounds(5, viewportGrid.getY(), 70, viewportGrid.getHeight()- 10);
    
    noteGrid.setBounds(0,0,4000, 20*127);
    noteGrid.setupGrid(900, 20);
    timelineComp.setBounds(0, 0, 100, viewportTimeline.getHeight());
    timelineComp.setup(10, 900);
    keyboardComp.setBounds(0, 0, viewportPiano.getWidth(), noteGrid.getHeight());
    
    noteGridPanel.setBounds(5, viewportGrid.getBottom() + 5, getWidth() - 10, 140);
    
    
}

void PianoRollEditorComponent::showControlPannel (bool state)
{
    noteGridPanel.setVisible(state);
}
void PianoRollEditorComponent::setStyleSheet (NoteGridStyleSheet style)
{
    //
}
void PianoRollEditorComponent::setup (const int bars, const int pixelsPerBar, const int noteHeight)
{
    noteGrid.setupGrid(pixelsPerBar, noteHeight);
    timelineComp.setup(bars, pixelsPerBar);
    keyboardComp.setSize(viewportPiano.getWidth(), noteGrid.getHeight()); //subtract 10 for the scroll bars
}

void PianoRollEditorComponent::loadSequence (PRESequence sequence)
{
    noteGrid.loadSequence(sequence);
    const int middleNote = ((sequence.highNote - sequence.lowNote) * 0.5) + sequence.lowNote;
    const float scrollRatio = middleNote / 127.0;
//    setScroll(0.0, scrollRatio);
}
PRESequence PianoRollEditorComponent::getSequence ()
{
    return noteGrid.getSequence();
}

void PianoRollEditorComponent::setScroll (double x, double y)
{
    viewportGrid.setViewPositionProportionately(x, y);
}
