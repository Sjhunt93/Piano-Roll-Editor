//
//  NoteComponent.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#include "NoteComponent.hpp"


NoteComponent::NoteComponent (NoteGridStyleSheet & ss) : styleSheet(ss), edgeResizer(this, nullptr, ResizableEdgeComponent::Edge::rightEdge)
{
    mouseOver = useCustomColour = false;
    addAndMakeVisible(edgeResizer);
    setMouseCursor(normal);
    startWidth = startX = startY = -1;
    coordiantesDiffer = false;
    isMultiDrag = false;
    
}
NoteComponent::~NoteComponent ()
{
    
}

void NoteComponent::paint (Graphics & g)
{
    g.fillAll(Colours::darkgrey); //border...
    Colour cToUse;
    if (useCustomColour) {
        cToUse = customColour;
    }
    else {
        cToUse = Colour::fromHSV(model.velocity/127.0, 1.0, 0.5, 0xFF);
        //(model.velocity/127.0) *
    }
    
    if (state || mouseOver) {
        cToUse = cToUse.brighter().brighter();
    }
    g.setColour(cToUse);
    
    //draw middle box.
    g.fillRect(1, 1, getWidth() - 2, getHeight() - 2);

    
    //draw velocity
    if (getWidth() > 10 && styleSheet.getDrawVelocity()) {
        g.setColour(cToUse.brighter());
        const int lineMax = getWidth() - 5;
        
        g.drawLine(5, getHeight() * 0.5 - 2, lineMax * (model.velocity/127.0), getHeight() * 0.5 - 2, 4);
    }
    String toDraw;
    if (styleSheet.getDrawMIDINoteStr()) {
        toDraw += String(pitches_names[model.note%12]) + String(model.note/12) + String(" ");
    }
    if (styleSheet.getDrawMIDINum()) {
        toDraw += String(model.note);
    }
    
    g.setColour(Colours::white);
    g.drawText(String(toDraw), 3, 3, getWidth() - 6, getHeight() - 6, Justification::centred);
    
}
void NoteComponent::resized ()
{
//    edgeResizer.setBounds(getWidth() - 10, getHeight(), 10, getHeight());
}
void NoteComponent::setCustomColour (Colour c)
{
    customColour = c;
    useCustomColour = true;
}

void NoteComponent::setValues (NoteModel m)
{
    
    
    if (m.note == 255) { m.note = 0; } //unsigned overflow
    if (m.note > 127) { m.note = 127; }
    
    if (((int)m.startTime) < 0) { m.startTime = 0; } //cast to int as noteLen is unsigned. allows us to check for 0
    model = m;
    repaint();

}
NoteModel NoteComponent::getModel ()
{
    return model;
}

void NoteComponent::setState (eState s)
{
    state = s;
    repaint();
}
NoteComponent::eState NoteComponent::getState ()
{
    return state;
}

void NoteComponent::mouseEnter (const MouseEvent&)
{
    mouseOver = true;
    repaint();
}
void NoteComponent::mouseExit  (const MouseEvent&)
{
    mouseOver = false;
    setMouseCursor(MouseCursor::NormalCursor);
    repaint();
    
}
void NoteComponent::mouseDown  (const MouseEvent& e)
{
//    startX = getX();
//    startY = getY();
    if (e.mods.isShiftDown()) {
        velocityEnabled = true;
        startVelocity = model.velocity;
    }
    else if (getWidth() - e.getMouseDownX() < 10) {
        resizeEnabled = true;
        startWidth = getWidth();
        
    }
    else {
        startDraggingComponent(this, e);
        wasDragging = true;
    }
    if (!resizeEnabled) {
        
    }
    
    
}
void NoteComponent::mouseUp    (const MouseEvent& e)
{
    if (onPositionMoved != nullptr) {
        onPositionMoved(this);
    }
    if (onNoteSelect != nullptr) {
        onNoteSelect(this, e);
    }
    startWidth = startX = startY -1;
    mouseOver = false;
    resizeEnabled = false;
    velocityEnabled = false;
    isMultiDrag = false;
    repaint();
    wasDragging = false;
    
}
void NoteComponent::mouseDrag  (const MouseEvent& e)
{
    //velocityEnabled
    if (resizeEnabled) {
        if (onLegnthChange != nullptr) {
            onLegnthChange(this, startWidth-e.getPosition().getX());
        }

    }
    else if (velocityEnabled) {
        int velocityDiff = e.getDistanceFromDragStartY() * -0.5;
        int newVelocity = startVelocity + velocityDiff;
        if (newVelocity < 1) {
            newVelocity = 1;
        }
        else if (newVelocity > 127) {
            newVelocity = 127;
        }
        model.velocity = newVelocity;
        repaint();
//        std::cout << velocityDiff << "\n";
        
    }
    else {
        setMouseCursor(MouseCursor::DraggingHandCursor);
        dragComponent(this, e, nullptr);
        
        if (onDragging != nullptr ) { //&& isMultiDrag
            onDragging(this, e);
        }
    }
    
}
void NoteComponent::mouseMove  (const MouseEvent& e)
{
    if (getWidth() - e.getMouseDownX() < 10) {
        setMouseCursor(MouseCursor::RightEdgeResizeCursor);
    }
    else {
        setMouseCursor(MouseCursor::NormalCursor);
    }
}

//MultiEditState NoteComponent::getMultiEditState ()
//{
//    
//}
//void NoteComponent::setMultiEditState (MultiEditState state)
//{
//    
//}
