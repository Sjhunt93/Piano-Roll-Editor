//
//  NoteModel.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 16/08/2019.
//

#include "NoteModel.hpp"

NoteModel::NoteModel ()
{
    
}
NoteModel::NoteModel (u8 n, u8 v, st_int st, st_int nl)
{
    note = n;
    velocity = v;
    startTime = st;
    noteLegnth = nl;
    
}
NoteModel::NoteModel (const NoteModel & other)
{
    note = other.note;
    velocity = other.velocity;
    startTime = other.startTime;
    noteLegnth = other.noteLegnth;
}



/*
 Quantising to say 1/8 notes would require an input value of 240 (or 0.5 * the default resolution)
 */
void NoteModel::quantiseModel (int qValue, bool qStartTime, bool qNoteLegnth)
{
    auto quantiseValue = [&](int qDiv, int valueToQuantise) -> int
    {
        //            const int lessThen = valueToQuantise % qDiv;
        const int simpleQ = (valueToQuantise / qDiv) * qDiv; //use lossey int division
        const int simpleQ1 = ((valueToQuantise / qDiv)+1) * qDiv; //use lossey int division
        if (valueToQuantise-simpleQ < simpleQ1-valueToQuantise) { //lower boundry
            return simpleQ;
        }
        return simpleQ1;
    };
    
    if (qStartTime) {
        startTime = quantiseValue(qValue, startTime);
    }
    if (qNoteLegnth) {
        noteLegnth = quantiseValue(qValue, noteLegnth);
        if (noteLegnth == 0) {
            noteLegnth = qValue; //
        }
    }
    
}

void PRESequence::print ()
{
    for (auto nm : events) {
        std::cout << (int) nm.note << " - " << (int) nm.velocity << " : " << nm.startTime << " - " << nm.noteLegnth << "\n";
    }
}
