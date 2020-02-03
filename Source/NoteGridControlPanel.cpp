//
//  NoteGridControlPanel.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 03/02/2020.
//

#include "NoteGridControlPanel.hpp"


NoteGridControlPanel::NoteGridControlPanel (NoteGridComponent & component) : noteGrid(component)
{
    addAndMakeVisible(noteCompHeight);
    addAndMakeVisible(pixelsPerBar);
    
    noteCompHeight.setRange(10, 30, 1);
    pixelsPerBar.setRange(700, 2000, 1);
    
    pixelsPerBar.setTextValueSuffix(" Pixels per bar");
    noteCompHeight.setTextValueSuffix(" Pixels per row");
    
    pixelsPerBar.setValue(900, dontSendNotification);
    noteCompHeight.setValue(20, dontSendNotification);
    
    pixelsPerBar.onValueChange = [this]()
    {
        noteGrid.setupGrid(pixelsPerBar.getValue(), noteCompHeight.getValue());
//        noteGrid.resized();
//        noteGrid.setSize(<#int newWidth#>, <#int newHeight#>)
        noteGrid.repaint();
    };
    noteCompHeight.onValueChange = pixelsPerBar.onValueChange;
    
    
}
NoteGridControlPanel::~NoteGridControlPanel ()
{
    
}

void NoteGridControlPanel::resized ()
{
    pixelsPerBar.setBounds(5, 5, 300, (getHeight() / 2) - 10);
    noteCompHeight.setBounds(5, pixelsPerBar.getBottom() + 5, 300, (getHeight() / 2) - 10);
    
}
void NoteGridControlPanel::paint (Graphics & g)
{
    
}
