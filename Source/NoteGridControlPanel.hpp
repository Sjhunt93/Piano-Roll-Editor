//
//  NoteGridControlPanel.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 03/02/2020.
//

#ifndef NoteGridControlPanel_hpp
#define NoteGridControlPanel_hpp


#include "PConstants.h"
#include "NoteGridComponent.hpp"
#include "NoteGridStyleSheet.hpp"

class NoteGridControlPanel : public Component {
public:
    NoteGridControlPanel (NoteGridComponent & component, NoteGridStyleSheet & styleSheet);
    ~NoteGridControlPanel ();
    
    void resized ();
    void paint (Graphics & g);
    
    void renderSequence ();
    std::function<void(int pixelsPerBar, int noteHeight)> configureGrid;
    
    void setQuantisation (PRE::eQuantisationValue value);
private:
    
    NoteGridComponent & noteGrid;
    NoteGridStyleSheet & styleSheet;
    
    Slider noteCompHeight, pixelsPerBar;
    
    TextButton render;
    ToggleButton drawMIDINotes, drawMIDIText, drawVelocity;
    
    ComboBox quantisationVlaue;
};

#endif /* NoteGridControlPanel_hpp */
