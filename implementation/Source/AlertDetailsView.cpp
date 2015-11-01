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

#include "AlertDetailsView.h"

AlertDetailsView::AlertDetailsView(): alert_(boost::none) {
    addAndMakeVisible(timerView_);
}

AlertDetailsView::~AlertDetailsView() {
}

void AlertDetailsView::paint(Graphics& g) {
    if (alert_) {
        JumpSeat::Alert alert = alert_.get();
        g.fillAll(Colours::black);
        
        int margin = 10;
        int lineHeight = getHeight() / 4;
        int lineWidth = getWidth() - margin * 2;
        
        g.setFont(lineHeight * 0.8);
        g.getCurrentFont().setBold(true);
        g.setColour(Colour::fromString(String(alert.type.colorHexCode)));
        
        g.drawText(String(alert.type.description), margin, 0, lineWidth, lineHeight, Justification::left, true);

        g.setColour(Colours::snow);
        if (alert.municipality) {
            g.drawText(String(alert.municipality.get()), margin, lineHeight, lineWidth, lineHeight, Justification::left, true);
        }
        if (alert.address) {
            g.drawText(String(alert.address.get()), margin, lineHeight * 2, lineWidth, lineHeight, Justification::left, true);
        }
        
        g.setColour(Colours::silver);
        g.getCurrentFont().setBold(false);
        if (alert.details) {
            g.drawText(String(alert.details.get()), margin, lineHeight * 3, lineWidth, lineHeight, Justification::left, true);
        }
    } else {
        g.fillAll(Colours::black);
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
    int h = getHeight() / 2;
    int w = getWidth();
    timerView_.setBounds(w - h * 2 - 20, 0, h * 2, h);
}

void AlertDetailsView::setAlert(boost::optional<JumpSeat::Alert> alert) {
    alert_ = alert;
    if (alert_) {
        timerView_.countUpFrom(alert_.get().timestamp);
    } else {
        timerView_.showClock();
    }
    repaint();
}
