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

#include "MainComponent.h"

MainContentComponent::MainContentComponent() {
    addAndMakeVisible(alertDetailsView_);
    addAndMakeVisible(responseDetailsView_);
    setSize(600, 600);
    
    // Sample
    
    JumpSeat::Alert alert;
    alert.type.code = "402";
    alert.type.description = "Byggnadsbrand: medelstor";
    alert.municipality = "PARGAS";
    alert.address = "SKOLGATAN,1";
    alert.details = "RVSPG31,RVSPG21,,,tilläggsinfo";
    
    alertDetailsView_.setAlert(alert);
    startFlashing(Colours::red);
}

MainContentComponent::~MainContentComponent() {
}

StringArray MainContentComponent::getMenuBarNames() {
    const char* const names[] = { "File", "Settings", "Testing", nullptr };
    return StringArray(names);
}

PopupMenu MainContentComponent::getMenuForIndex(int topLevelMenuIndex, const String& menuName) {
    PopupMenu menu;
    
    switch (topLevelMenuIndex) {
        case 0: { // File
            menu.addItem(100, "Reset");
            menu.addSeparator();
            menu.addItem(101, "Show SMS Log...");
            menu.addItem(102, "Show Phone Call Log...");
            menu.addItem(103, "Show Alert Log...");
            menu.addSeparator();
            menu.addItem(104, "Import...");
            menu.addItem(105, "Export...");
#if !JUCE_MAC
            menu.addSeparator();
            menu.addItem(106, "Exit");
#endif
            break;
        }
        case 1: { // Settings
            menu.addItem(200, "Alert Types...");
            menu.addItem(201, "Responders...");
            menu.addItem(202, "Responder Status Codes...");
            menu.addSeparator();
            menu.addItem(203, "Modem...");
            break;
        }
        case 2: { // Testing
            menu.addItem(300, "Simulate phone call...");
            menu.addItem(301, "Simulate SMS...");
            break;
        }
    }
    
    return menu;
}

void MainContentComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    
}

void MainContentComponent::startFlashing(const Colour &color) {
    flashColor_ = color;
    flashAlpha_ = 1.0f;
    isFlashing_ = true;
    startTimerHz(25);
    repaint();
}

void MainContentComponent::stopFlashing() {
    isFlashing_ = false;
    stopTimer();
    repaint();
}

void MainContentComponent::timerCallback() {
    flashAlpha_ -= 0.04f;
    if (flashAlpha_ < 0.05f) {
        flashAlpha_ = 1.0f;
    }
    repaint();
}

void MainContentComponent::paint(Graphics& g) {
    if (isFlashing_) {
        g.fillAll(flashColor_.overlaidWith(Colours::black.withAlpha(flashAlpha_)));
    }
    
   /* g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);*/
}

void MainContentComponent::resized() {
    const int margin = 20;
    int h = (getHeight() - margin * 2) / 4;
    int w = (getWidth() - margin * 2);
    alertDetailsView_.setBounds(margin, margin, w, h);
    responseDetailsView_.setBounds(margin, h + margin * 2, w, h * 3 - margin);
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}


