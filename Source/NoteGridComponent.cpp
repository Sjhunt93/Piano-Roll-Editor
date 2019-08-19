//
//  NoteGridComponent.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#include "NoteGridComponent.hpp"
#include <array>




NoteGridComponent::NoteGridComponent ()
{
    blackPitches.add(1);
    blackPitches.add(3);
    blackPitches.add(6);
    blackPitches.add(8);
    blackPitches.add(10);
    addChildComponent(&selectorBox);
    addKeyListener(this);
    setWantsKeyboardFocus(true);
}
NoteGridComponent::~NoteGridComponent ()
{
    
}

void NoteGridComponent::paint (Graphics & g)
{
    g.fillAll(Colours::darkgrey);
    
    const int totalBars = (getWidth() / pixelsPerBar) + 1;
    
    
    {
        float line = 0;//noteCompHeight;
        
        for (int i = 127; i >= 0; i--) {
            
            if (blackPitches.contains(i%12)) {
                g.setColour(Colours::darkgrey.withAlpha(0.5f));
            }
            else {
                g.setColour(Colours::lightgrey.darker().withAlpha(0.5f));
            }
            g.fillRect(0, (int)line, getWidth(), (int)noteCompHeight);
            line += noteCompHeight;
            g.setColour(Colours::black);
            g.drawLine(0, line, getWidth(), line);
        }
    }
    
    
    const float increment = pixelsPerBar / 16;
    float line = 0;
    g.setColour(Colours::lightgrey);
    for (int i = 0; line < getWidth() ; i++) {
        float lineThickness = 1.0;
        if (i % 16 == 0) { //bar marker
            lineThickness = 3.0;
        }
        else if (i % 4 == 0) { //1/4 div
            lineThickness = 2.0;
        }
        g.drawLine(line, 0, line, getHeight(), lineThickness);
        
        line += increment;
    }
    
    
    
//    for (int i = 0; i < )
}
void NoteGridComponent::resized ()
{
    
    //    void mouseDoubleClick (const MouseEvent&);
    for (NoteComponent * component : noteComps) {
        if (component->coordiantesDiffer) {
            noteCompPositionMoved(component, false);
        }
        const float xPos = (component->getModel().startTime / ((float) ticksPerTimeSignature)) * pixelsPerBar;
        const float yPos = getHeight() - ((component->getModel().note / 127.0) * getHeight());
        float len = (component->getModel().noteLegnth / ((float) ticksPerTimeSignature)) * pixelsPerBar;
        
        component->setBounds(xPos, yPos, len, noteCompHeight);
    }
    
    
}




void NoteGridComponent::setupGrid (float px, float compHeight)
{
    pixelsPerBar = px;
    noteCompHeight = compHeight;
}

void NoteGridComponent::noteCompSelected (NoteComponent * nc)
{
    for (NoteComponent * component : noteComps) {
        if (component == nc) {
            component->setState(NoteComponent::eSelected);
            component->toFront(true);
        }
        else {
            component->setState(NoteComponent::eNone);
        }
    }
}
void NoteGridComponent::noteCompPositionMoved (NoteComponent * comp, bool callResize)
{
    int xPos = (comp->getX() / ((float)pixelsPerBar)) * ticksPerTimeSignature;
    int note = 127 - (comp->getY() / noteCompHeight);
    if (note > 127) {
        note = 127;
    }
    else if (note < 0) {
        note = 0;
    }
    
    if (xPos <= 0) {
        xPos = 0;
    }
    
    const int len = (comp->getWidth() / ((float)pixelsPerBar)) * ticksPerTimeSignature;
    NoteModel nm = comp->getModel();
    nm.note = note;
    nm.startTime = xPos;
    nm.noteLegnth = len;
    nm.quantiseModel(defaultResolution / 8, true, true);
    
    comp->setValues(nm);
    if (callResize) {
        resized();
    }
}

void NoteGridComponent::noteCompLengthChanged (NoteComponent * original, int diff)
{
    for (auto n : noteComps) {
        if (n->getState() == NoteComponent::eSelected && n != original) {
            if (n->startWidth == -1) {
                n->startWidth = n->getWidth();
                n->coordiantesDiffer = true;
            }
            
            const int newWidth = n->startWidth - diff;
            if (newWidth > 20) {
                n->setSize(newWidth, n->getHeight());
            }
                
            
        }
    }
}

void NoteGridComponent::setPositions ()
{
    
}

void NoteGridComponent::mouseDown (const MouseEvent&)
{
    for (NoteComponent * component : noteComps) {
        component->setState(NoteComponent::eNone);
    }
}
void NoteGridComponent::mouseDrag (const MouseEvent& e)
{
    if (!selectorBox.isVisible()) {
        selectorBox.setVisible(true);
        selectorBox.toFront(false);
        
        selectorBox.setTopLeftPosition(e.getPosition());
        
        
    }
    else {
        selectorBox.setSize(e.getPosition().getX() - selectorBox.getX(), e.getPosition().getY() - selectorBox.getY());
    }
}
void NoteGridComponent::mouseUp (const MouseEvent&)
{
    if (selectorBox.isVisible()) {
        
        
        for (NoteComponent * component : noteComps) {
            if (component->getBounds().intersects(selectorBox.getBounds())) {
                component->setState(NoteComponent::eState::eSelected);
            }
            else {
                component->setState(NoteComponent::eState::eNone);
            }
        }
        selectorBox.setVisible(false);
        selectorBox.toFront(false);
        selectorBox.setSize(1,1);
    }
    
    
}

void NoteGridComponent::mouseDoubleClick (const MouseEvent& e)
{
    const int xPos = (e.getMouseDownX() / ((float)pixelsPerBar)) * ticksPerTimeSignature;
    const int note = 128 - (e.getMouseDownY() / noteCompHeight);
    jassert(note >= 0 && note < 127);
    
    NoteComponent * nn = new NoteComponent();
    nn->onNoteSelect = [this](NoteComponent * n) {
        this->noteCompSelected(n);
    };
    nn->onPositionMoved = [this](NoteComponent * n) {
        this->noteCompPositionMoved(n);
    };
    nn->onLegnthChange = [this](NoteComponent * n, int diff) {
        this->noteCompLengthChanged(n, diff);
    };
    addAndMakeVisible(nn);
    nn->setValues({(u8)note, (u8) ((arc4random() % 60) + 60), (st_int)xPos, 480/2});
    noteComps.push_back(nn);
    resized();
    repaint();
}



bool NoteGridComponent::keyPressed (const KeyPress& key, Component* originatingComponent)
{
    if (key == KeyPress::backspaceKey) {
        //
        deleteAllSelected();
        return true;
    }
    if (key == KeyPress::spaceKey) {
        //
        getSequence();
        return true;
    }
    return false;
}

void NoteGridComponent::deleteAllSelected ()
{
    std::vector<NoteComponent *> itemsToKeep;
    for (int i = 0; i < noteComps.size(); i++) {
        if (noteComps[i]->getState() == NoteComponent::eSelected) {
            removeChildComponent(noteComps[i]);
            delete noteComps[i];
        }
        else {
            itemsToKeep.push_back(noteComps[i]);
        }
    }
    noteComps = itemsToKeep;
}

Sequence NoteGridComponent::getSequence ()
{
    int leftToSort = noteComps.size();
    

    
    std::vector<NoteComponent *> componentsCopy = noteComps;
    auto findLowest = [&]() -> int {
        int lowestIndex = 0;
        for (int i = 0; i < componentsCopy.size(); i++) {
            if (componentsCopy[i]->getModel().startTime < componentsCopy[lowestIndex]->getModel().startTime) {
                lowestIndex = i;
            }
        }
        return lowestIndex;
    };
    
    
    Sequence seq;
    while (leftToSort) {
        const int index = findLowest();
        seq.events.push_back(componentsCopy[index]->getModel());
        componentsCopy.erase(componentsCopy.begin() + index);
        leftToSort--;
    }
    seq.print();
    return seq;
}
