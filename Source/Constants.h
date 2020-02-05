//
//  Constants.h
//  PianoRollEditor
//
//  Created by Samuel Hunt on 16/08/2019.
//

#ifndef Constants_h
#define Constants_h

typedef unsigned char u8;
typedef unsigned int st_int;

static const int defaultResolution = 480; // per quarter note


static const char * pitches_names[] = {
    "C",
    "C#",
    "D",
    "D#",
    "E",
    "F",
    "F#",
    "G",
    "G#",
    "A",
    "A#",
    "B",
};

enum eQuantisationValue {
    eQuantisationValueNone = 0,
    eQuantisationValue1_32,
    eQuantisationValue1_16,
    eQuantisationValue1_8,
    eQuantisationValue1_4,
    eQuantisationValueTotal,
};

const int quantisedDivisionValues[eQuantisationValueTotal] = {
    1,
    (defaultResolution / 8),
    (defaultResolution / 4),
    (defaultResolution / 2),
    defaultResolution
};

#endif /* Constants_h */
