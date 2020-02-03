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
    friend class NoteGridControlPannel; //we use to ensure a one way only relationship. The control pannel can set member varialbes but nothing else can...
    
    bool getDrawMIDINum ();
    bool getDrawMIDINoteStr ();
    
    
private:
    bool drawMIDINum;
    bool drawMIDINoteStr;
    
};

#endif /* NoteGridStyleSheet_hpp */
