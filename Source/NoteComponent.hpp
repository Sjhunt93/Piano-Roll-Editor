//
//  NoteComponent.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#ifndef NoteComponent_hpp
#define NoteComponent_hpp


#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteModel.hpp"
#include "NoteGridStyleSheet.hpp"

class NoteComponent :
public Component,
public ComponentDragger
{
public:
    
    enum eState {
        eNone,
        eSelected,
    };
    struct MultiEditState {
        int startWidth; //used when resizing the noteComponents length
        bool coordiantesDiffer; //sometimes the size of this component gets changed externally (for example on multi-resizing) set this flag to be true and at
        Rectangle<int> startingBounds;
    };
    
    NoteComponent (NoteGridStyleSheet & styleSheet);
    ~NoteComponent ();
    
    void paint (Graphics & g);
    void resized ();
    void setCustomColour (Colour c);
    
    void setValues (NoteModel model);
    NoteModel getModel ();
    
    void setState (eState state);
    eState getState ();
    
    void mouseEnter (const MouseEvent&);
    void mouseExit  (const MouseEvent&);
    void mouseDown  (const MouseEvent&);
    void mouseUp    (const MouseEvent&);
    void mouseDrag  (const MouseEvent&);
    void mouseMove  (const MouseEvent&);
    
    
//    void mouseDoubleClick (const MouseEvent&);
    
    std::function<void(NoteComponent*, const MouseEvent&)> onNoteSelect;
    std::function<void(NoteComponent*)> onPositionMoved;
//    std::function<void(NoteComponent*, int, int)> onDragging;
    std::function<void(NoteComponent*, const MouseEvent&)> onDragging; //send the drag event to other components..
    std::function<void(NoteComponent*, int)> onLegnthChange; //sends the difference as this is relative for all components.
    
    int minWidth = 20;
    int startWidth; //used when resizing the noteComponents length
    bool coordiantesDiffer; //sometimes the size of this component gets changed externally (for example on multi-resizing) set this flag to be true and at some point the internal model will get updated also
//    MultiEditState getMultiEditState ();
//    void setMultiEditState (MultiEditState state);
    MultiEditState mEditState;

private:
    NoteGridStyleSheet & styleSheet;
    ResizableEdgeComponent edgeResizer;
    
    bool mouseOver, useCustomColour, resizeEnabled, velocityEnabled;
    int startVelocity;
    Colour customColour;
    NoteModel model;
    MouseCursor normal;
    eState state;

};

#endif /* NoteComponent_hpp */
