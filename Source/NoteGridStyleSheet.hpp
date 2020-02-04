//
//  NoteGridStyleSheet.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 03/02/2020.
//

#ifndef NoteGridStyleSheet_hpp
#define NoteGridStyleSheet_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class NoteGridStyleSheet {
public:
    friend class NoteGridControlPanel; //we use to ensure a one way only relationship. The control pannel can set member varialbes but nothing else can...
    
    NoteGridStyleSheet ();
    
    bool getDrawMIDINum ();
    bool getDrawMIDINoteStr ();
    bool getDrawVelocity ();
    
private:
    bool drawMIDINum, drawMIDINoteStr, drawVelocity;
    
    
};

#endif /* NoteGridStyleSheet_hpp */
