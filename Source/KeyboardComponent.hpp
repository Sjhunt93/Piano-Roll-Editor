//
//  KeyboardComponent.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 04/02/2020.
//

#ifndef KeyboardComponent_hpp
#define KeyboardComponent_hpp

#include "PConstants.h"

class KeyboardComponent : public Component {
public:
    
    KeyboardComponent ();
    void paint (Graphics & g);
    
private:
    Array<int> blackPitches;

};

#endif /* KeyboardComponent_hpp */
