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
    
    noteGrid.onEdit = [this]() //pass up the chain.
    {
        if (this->onEdit != nullptr) {
            this->onEdit();
        }
    };
    noteGrid.sendChange = [this](int note, int vel)
    {
        if (this->sendChange != nullptr) {
            this->sendChange(note, vel);
        }
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
    noteGrid.setupGrid(900, 20, 10);
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
    noteGrid.setupGrid(pixelsPerBar, noteHeight, bars);
    timelineComp.setup(bars, pixelsPerBar);
    keyboardComp.setSize(viewportPiano.getWidth(), noteGrid.getHeight()); //subtract 10 for the scroll bars
}

void PianoRollEditorComponent::updateBars (const int newNumberOfBars)
{
    const float pPb = noteGrid.getPixelsPerBar();
    const float nH = noteGrid.getNoteCompHeight();
    noteGrid.setupGrid(pPb, nH, newNumberOfBars);
    timelineComp.setup(newNumberOfBars, pPb);
    keyboardComp.setSize(viewportPiano.getWidth(), noteGrid.getHeight());
    
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
void PianoRollEditorComponent::disableEditing (bool value)
{
    styleSheet.disableEditing = value;
    noteGrid.repaint();
}

NoteGridControlPanel & PianoRollEditorComponent::getControlPannel ()
{
    return noteGridPanel;
}

PianoRollEditorComponent::ExternalModelEditor PianoRollEditorComponent::getSelectedNoteModels ()
{
    ExternalModelEditor mEdit;
    mEdit.update = [this]()
    {
        noteGrid.resized();
        noteGrid.repaint();
    };
    mEdit.models = noteGrid.getSelectedModels();
    return mEdit;
}
