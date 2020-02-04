/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : noteGrid(styleSheet), noteGridPanel(noteGrid, styleSheet)
{
    setSize (800, 600);
    
    addAndMakeVisible(viewportGrid);
//    viewport.setScrollOnDragEnabled(true);
    viewportGrid.setViewedComponent(&noteGrid, false);
    viewportGrid.setScrollBarsShown(true, true);
    viewportGrid.setScrollBarThickness(10);
//    viewport.setColour(Colourids
    addAndMakeVisible(noteGridPanel);
    
    viewportTimeline.setViewedComponent(&timelineComp, false);
    viewportTimeline.setScrollBarsShown(false, false);
    addAndMakeVisible(viewportTimeline);
    
    viewportPiano.setViewedComponent(&keyboardComp, false);
    viewportPiano.setScrollBarsShown(false, false);
    addAndMakeVisible(viewportPiano);
    
    viewportGrid.positionMoved = [this](int x, int y)
    {
        viewportTimeline.setViewPosition(x, y);
        viewportPiano.setViewPosition(x, y);
    };
    
    noteGridPanel.configureGrid = [this](int pixelsPerBar, int noteHeight)
    {
        noteGrid.setupGrid(pixelsPerBar, noteHeight);
        timelineComp.setup(10, pixelsPerBar);
        keyboardComp.setSize(viewportPiano.getWidth(), noteGrid.getHeight()); //subtract 10 for the scroll bars

    };
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    viewportGrid.setBounds(80, 50, getWidth()-90, getHeight()-180);
    viewportTimeline.setBounds(viewportGrid.getX(), 5, viewportGrid.getWidth()-10, viewportGrid.getY() - 5);
    viewportPiano.setBounds(5, viewportGrid.getY(), 70, viewportGrid.getHeight()- 10);
    
    noteGrid.setBounds(0,0,4000, 20*127);
    noteGrid.setupGrid(900, 20);
    timelineComp.setBounds(0, 0, 100, viewportTimeline.getHeight());
    timelineComp.setup(10, 900);
    keyboardComp.setBounds(0, 0, viewportPiano.getWidth(), noteGrid.getHeight());
    
    noteGridPanel.setBounds(5, viewportGrid.getBottom() + 5, getWidth() - 10, 140);
    
    

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
