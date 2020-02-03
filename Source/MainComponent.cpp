/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : noteGridPanel(noteGrid)
{
    setSize (800, 600);
    
    addAndMakeVisible(viewport);
//    viewport.setScrollOnDragEnabled(true);
    viewport.setViewedComponent(&noteGrid);
    viewport.setScrollBarsShown(true, true);
    viewport.setScrollBarThickness(10);
//    viewport.setColour(Colourids
    addAndMakeVisible(noteGridPanel);
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
    viewport.setBounds(10, 10, getWidth()-10, getHeight()-150);
    noteGrid.setBounds(0,0,4000, 20*127);
    noteGrid.setupGrid(900, 20);
    noteGrid.resized();
    
    noteGridPanel.setBounds(5, viewport.getBottom() + 5, getWidth() - 10, 140);
    
    

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
