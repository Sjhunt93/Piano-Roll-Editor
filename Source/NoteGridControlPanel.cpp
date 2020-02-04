//
//  NoteGridControlPanel.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 03/02/2020.
//

#include "NoteGridControlPanel.hpp"


NoteGridControlPanel::NoteGridControlPanel (NoteGridComponent & component, NoteGridStyleSheet & ss) : noteGrid(component), styleSheet(ss)
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
        if (configureGrid) {
            configureGrid(pixelsPerBar.getValue(), noteCompHeight.getValue());
        }
//        noteGrid.setupGrid(pixelsPerBar.getValue(), noteCompHeight.getValue());
//        noteGrid.repaint();
    };
    noteCompHeight.onValueChange = pixelsPerBar.onValueChange;
    
    
    addAndMakeVisible(drawMIDINotes);
    addAndMakeVisible(drawMIDIText);
    addAndMakeVisible(drawVelocity);
    addAndMakeVisible(render);
    
    
    render.setButtonText("Render");
    drawMIDINotes.setButtonText("Draw MIDI Notes");
    drawMIDIText.setButtonText("Draw MIDI Text");
    drawVelocity.setButtonText("Draw Velocity");
    
    render.onClick = [this]()
    {
        renderSequence();
    };
    
    drawMIDIText.onClick = [this]()
    {
        styleSheet.drawMIDINoteStr = drawMIDIText.getToggleState();
        styleSheet.drawMIDINum = drawMIDINotes.getToggleState();
        styleSheet.drawVelocity = drawVelocity.getToggleState();
        noteGrid.repaint();
    };
    drawVelocity.onClick = drawMIDINotes.onClick = drawMIDIText.onClick;
}
NoteGridControlPanel::~NoteGridControlPanel ()
{
    
}

void NoteGridControlPanel::resized ()
{
    pixelsPerBar.setBounds(5, 5, 300, (getHeight() / 2) - 10);
    noteCompHeight.setBounds(5, pixelsPerBar.getBottom() + 5, 300, (getHeight() / 2) - 10);
    
    drawMIDINotes.setBounds(pixelsPerBar.getRight() + 5, 5, 200, (getHeight() / 3) - 10);
    drawMIDIText.setBounds(pixelsPerBar.getRight() + 5, drawMIDINotes.getBottom() + 5, 200, drawMIDINotes.getHeight());
    drawVelocity.setBounds(pixelsPerBar.getRight() + 5, drawMIDIText.getBottom() + 5, 200, drawMIDINotes.getHeight());
    
    render.setBounds(getWidth() - 100, 5, 95, 40);
    
    
}
void NoteGridControlPanel::paint (Graphics & g)
{
    
}

void NoteGridControlPanel::renderSequence ()
{
    
}
