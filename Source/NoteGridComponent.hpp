//
//  NoteGridComponent.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#ifndef NoteGridComponent_hpp
#define NoteGridComponent_hpp

#include "NoteComponent.hpp"

class SelectionBox : public Component {
    void paint (Graphics & g)
    {
        Colour c = Colours::white;
        c = c.withAlpha((float)0.5);
        g.fillAll(c);
    }
};

class NoteGridComponent :
public Component,
public KeyListener
{
public:
    

    NoteGridComponent ();
    ~NoteGridComponent ();
    
    void paint (Graphics & g);
    void resized ();
    
    void noteCompSelected (NoteComponent *, const MouseEvent&);
    void noteCompPositionMoved (NoteComponent *, bool callResize = true);
    void noteCompLengthChanged (NoteComponent *, int diff);
    void noteCompDragging (NoteComponent*, const MouseEvent&);
    void setPositions ();
    
    /*
    void mouseEnter (const MouseEvent&);
    void mouseExit  (const MouseEvent&);
    void mouseDown  (const MouseEvent&);
    void mouseUp    (const MouseEvent&);
    void mouseDrag  (const MouseEvent&);
    void mouseMove  (const MouseEvent&);
    */
    void mouseDown  (const MouseEvent&);
    void mouseDrag  (const MouseEvent&);
    void mouseUp    (const MouseEvent&);
    void mouseDoubleClick (const MouseEvent&);
    
    void setupGrid (float pixelsPerBar, float compHeight);
    
    bool keyPressed (const KeyPress& key, Component* originatingComponent);
    void deleteAllSelected ();
    
    // From here you could convert this into MIDI or anyother custom musical encoding.
    Sequence getSequence ();
    
private:
    std::vector<NoteComponent *> noteComps;
    float noteCompHeight;
    float pixelsPerBar;
    st_int ticksPerTimeSignature = defaultResolution * 4; //4/4 assume
    
    Array<int> blackPitches;
    
    SelectionBox selectorBox;
};
#endif /* NoteGridComponent_hpp */
