//
//  NoteGridControlPanel.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 03/02/2020.
//

#ifndef NoteGridControlPanel_hpp
#define NoteGridControlPanel_hpp


#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteGridComponent.hpp"

class NoteGridControlPanel : public Component {
public:
    NoteGridControlPanel (NoteGridComponent & component);
    ~NoteGridControlPanel ();
    
    void resized ();
    void paint (Graphics & g);
    
private:
    
    NoteGridComponent & noteGrid;
    
    Slider noteCompHeight;
    Slider pixelsPerBar;
};

#endif /* NoteGridControlPanel_hpp */
