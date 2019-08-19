//
//  NoteComponent.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#include "NoteComponent.hpp"


NoteComponent::NoteComponent () : edgeResizer(this, nullptr, ResizableEdgeComponent::Edge::rightEdge)
{
    mouseOver = useCustomColour = false;
    addAndMakeVisible(edgeResizer);
    setMouseCursor(normal);
    startWidth = -1;
    coordiantesDiffer = false;
}
NoteComponent::~NoteComponent ()
{
    
}

void NoteComponent::paint (Graphics & g)
{
    g.fillAll(Colours::darkgrey);
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
    g.fillRect(1, 1, getWidth() - 2, getHeight() - 2);
//    g.drawLine(<#float startX#>, <#float startY#>, <#float endX#>, <#float endY#>)
    if (getWidth() > 10) {
        g.setColour(cToUse.brighter());
        const int lineMax = getWidth() - 5;
        
        g.drawLine(5, getHeight() * 0.5 - 2, lineMax * (model.velocity/127.0), getHeight() * 0.5 - 2, 4);
    }
    
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
    
    if (getWidth() - e.getMouseDownX() < 10) {
        resizeEnabled = true;
        startWidth = getWidth();
    }
    else {
        startDraggingComponent(this, e);
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
    startWidth = -1;
    mouseOver = false;
    resizeEnabled = false;
    repaint();
    
}
void NoteComponent::mouseDrag  (const MouseEvent& e)
{
    if (!resizeEnabled) {
        setMouseCursor(MouseCursor::DraggingHandCursor);
        dragComponent(this, e, nullptr);
//        if (onDragging != nullptr) {
//            onDragging(this, e);
//        }
    }
    else {
            if (onLegnthChange != nullptr) {
                onLegnthChange(this, startWidth-e.getPosition().getX());
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
