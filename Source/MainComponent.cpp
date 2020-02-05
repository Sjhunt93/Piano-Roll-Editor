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
    editor.setup(10, 900, 20); //default 10 bars..
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void MainComponent::resized()
{
    editor.setBounds(0, 0, getWidth(), getHeight());
}
