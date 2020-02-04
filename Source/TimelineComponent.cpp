//
//  TimelineComponent.cpp
//  PianoRollEditor - App
//
//  Created by Samuel Hunt on 04/02/2020.
//

#include "TimelineComponent.hpp"


TimelineComponent::TimelineComponent ()
{
    
}
void TimelineComponent::setup (const int bd, const int px)
{
    barsToDraw = bd;
    pixelsPerBar = px;
    setSize(pixelsPerBar * barsToDraw, getHeight()); //height is set externally.
}
void TimelineComponent::paint (Graphics & g)
{
    g.fillAll(Colours::darkgrey);

    
    const int marks = barsToDraw * 4; //assume 4/4
    const float increment = getWidth() / (float)(marks);
    float yPos = 0;
    g.setColour(Colours::white);
    for (int i = 0; i < marks; i++) {
        
        if (i % 4 == 0) {
            g.drawText(String(i/4 + 1), yPos + 5, 3, 30, 20, Justification::left);
            g.drawLine(yPos, 0, yPos, getHeight());
        }
        else if ( i % 2 == 0) {
            g.drawLine(yPos, getHeight() * 0.66, yPos, getHeight());
        }
        else {
            g.drawLine(yPos, getHeight() * 0.33, yPos, getHeight());
        }
        
        
        yPos += increment;
    }
}
void TimelineComponent::resized ()
{
    
}
