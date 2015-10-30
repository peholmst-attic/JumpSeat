/*
 * JumpSeat
 * Copyright (C) 2015 Petter Holmström
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "ResponseDetailsView.h"

//==============================================================================
ResponseDetailsView::ResponseDetailsView()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ResponseDetailsView::~ResponseDetailsView()
{
}

void ResponseDetailsView::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

/*    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("ResponseDetailsView", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text*/
}

void ResponseDetailsView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
