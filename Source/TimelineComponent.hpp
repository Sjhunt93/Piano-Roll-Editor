//
//  TimelineComponent.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 04/02/2020.
//

#ifndef TimelineComponent_hpp
#define TimelineComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class TimelineComponent : public Component {
public:
    
    TimelineComponent ();
    
    void setup (const int barsToDraw, const int pixelsPerBar);
    void paint (Graphics & g);
    void resized ();
private:
    int barsToDraw;
    int pixelsPerBar;
};

#endif /* TimelineComponent_hpp */
