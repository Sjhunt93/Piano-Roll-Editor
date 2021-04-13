/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    addAndMakeVisible(editor);
    editor.setup(10, 900, 20); //default 10 bars, with 900 pixels per bar (width) and 20 pixels per step (each note height)
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //unused
}

void MainComponent::resized()
{
    editor.setBounds(0, 0, getWidth(), getHeight());
}
