//
//  NoteModel.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#ifndef NoteModel_hpp
#define NoteModel_hpp

#include "Constants.h"
#include <vector>
#include <iostream>

class NoteModel {
public:
    u8 note;
    u8 velocity;
    st_int startTime;
    st_int noteLegnth;
    
    /*
     Quantising to say 1/8 notes would require an input value of 240 (or 0.5 * the default resolution)
     */
    void quantiseModel (int qValue, bool qStartTime, bool qNoteLegnth)
    {
        auto quantiseValue = [&](int qDiv, int valueToQuantise) -> int
        {
            const int lessThen = valueToQuantise % qDiv;
            const int simpleQ = (valueToQuantise / qDiv) * qDiv; //use lossey int division
            const int simpleQ1 = ((valueToQuantise / qDiv)+1) * qDiv; //use lossey int division
            if (valueToQuantise-simpleQ < simpleQ1-valueToQuantise) {
                return simpleQ;
            }
            return simpleQ1;
        };
        
        if (qStartTime) {
            startTime = quantiseValue(qValue, startTime);
        }
        if (qNoteLegnth) {
            noteLegnth = quantiseValue(qValue, noteLegnth);
        }
        
    }
};

class Sequence {
public:
    std::vector<NoteModel> events;
    int tsLow;
    int tsHight;
    
    void print ()
    {
        for (auto nm : events) {
            std::cout << (int) nm.note << " - " << (int) nm.velocity << " : " << nm.startTime << " - " << nm.noteLegnth << "\n";
        }
    }
};

#endif /* NoteModel_hpp */
