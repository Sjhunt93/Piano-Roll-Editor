//
//  NoteModel.hpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#ifndef NoteModel_hpp
#define NoteModel_hpp

#include "PConstants.h"
#include <vector>
#include <iostream>

class NoteModel {
public:
    
    NoteModel ();
    NoteModel (u8 n, u8 v, st_int st, st_int nl, int flags);
    NoteModel (const NoteModel & other);
    
    
    void quantiseModel (int qValue, bool qStartTime, bool qNoteLegnth);
    
    bool compare (const NoteModel & other, bool compareUIDs = true);
    
    u8 note;
    u8 velocity;
    st_int startTime;
    st_int noteLegnth;
    unsigned int flags; //the first 8 bits are for custom colours that you might want to map.
#ifndef LIB_VERSION
    int64_t        uniqueId;
#endif
};

class PRESequence { //Piano Roll Editor Sequence
public:
    std::vector<NoteModel> events;
    int tsLow;
    int tsHight;
    
    int lowNote;
    int highNote;
    
    void print ();
};

#endif /* NoteModel_hpp */
