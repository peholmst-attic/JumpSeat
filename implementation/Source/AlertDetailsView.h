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

#ifndef ALERTDETAILSVIEW_H_INCLUDED
#define ALERTDETAILSVIEW_H_INCLUDED

#include <boost/optional.hpp>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Alert.h"
#include "TimerView.h"

class AlertDetailsView: public Component {
public:
    AlertDetailsView();
    ~AlertDetailsView();

    void paint(Graphics& g) override;
    void resized() override;
    
    void setAlert(boost::optional<JumpSeat::Alert> alert);
private:
    TimerView timerView_;
    boost::optional<JumpSeat::Alert> alert_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlertDetailsView)
};

#endif  // ALERTDETAILSVIEW_H_INCLUDED
