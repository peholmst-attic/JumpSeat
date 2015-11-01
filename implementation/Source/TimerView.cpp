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

#include "TimerView.h"

TimerView::TimerView() {
    startTimerHz(2);
}

TimerView::~TimerView() {
    stopTimer();
}

void TimerView::paint (Graphics& g) {
    std::string timeString;
    if (countUpFrom_) {
        timeString = JumpSeat::Duration(countUpFrom_.get(), JumpSeat::DateTime()).toString();
    } else {
        timeString = JumpSeat::DateTime().toString("%T");
    }
    
    Font font = Font(Font::getDefaultSansSerifFontName(), 20.0f, 0);
    float scale = (float) getWidth() / (float) font.getStringWidth(timeString);
    g.setFont(font.withHeight(font.getHeight() * scale));
    
    g.setColour(Colours::snow);
    g.drawText(timeString, getLocalBounds(), Justification::centred);
}

void TimerView::resized() {
    repaint();
}

void TimerView::timerCallback() {
    repaint();
}

void TimerView::countUpFrom(const JumpSeat::DateTime& dateTime) {
    countUpFrom_ = dateTime;
    repaint();
}

void TimerView::showClock() {
    countUpFrom_ = boost::none;
    repaint();
}