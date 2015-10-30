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
#include "AlertDetailsView.h"

AlertDetailsView::AlertDetailsView(): alert_(boost::none) {
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AlertDetailsView::~AlertDetailsView() {
}

void AlertDetailsView::paint(Graphics& g) {
    if (alert_) {
        JumpSeat::Alert alert = alert_.get();
        g.fillAll(Colours::black);
        g.setColour(Colours::whitesmoke);
        
        g.setFont(20.f);
        g.drawSingleLineText(String(alert.type.code), 5, 5, Justification::left);
        g.drawSingleLineText(String(alert.type.description), 20, 20, Justification::left);
    } else {
        g.fillAll(Colours::white);
    }
//    g.fillAll (Colour::fromString(<#juce::StringRef encodedColourString#>));   // clear the background

//    g.setColour (Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

//    g.setColour (Colours::lightblue);
//    g.setFont (14.0f);
//    g.drawText ("AlertDetailsView", getLocalBounds(),
//                Justification::centred, true);   // draw some placeholder text
}

void AlertDetailsView::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AlertDetailsView::setAlert(boost::optional<JumpSeat::Alert> alert) {
    alert_ = alert;
    repaint();
}
