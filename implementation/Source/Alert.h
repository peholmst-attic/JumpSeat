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

#ifndef ALERT_H
#define	ALERT_H

#include <string>
#include <boost/optional.hpp>
#include <boost/signals2/signal.hpp>

#include "AlertType.h"
#include "Time.h"

namespace JumpSeat {

    /**
     * A structure containing information about an alert.
     */
    struct Alert {
        AlertType type; /**< the type of the alert (e.g. structure fire, MVA, automatic fire alarm, etc.) */
        boost::optional<std::string> municipality; /**< the municipaliy in which the incident occured, if available */
        boost::optional<std::string> address; /**< the address of the incident, if available */
        boost::optional<std::string> details; /**< the details of the incident, if available */
        std::string message; /**< the complete original alert message */
        DateTime timestamp; /**< the date and time when the alert was received */
    };

    /**
     * An enumeration of the different fields in an alert message. It
     * is used when parsing an arriving alert message into an Alert structure.
     */
    enum class AlertField {
        code, /**< the alert code to be passed to the AlertTypeRepository when retrieving the AlertType */
        municipality, /**< the municipality of the incident */
        address, /**< the address of the incident */
        details /**< any other details about the incident */
    };

    typedef boost::signals2::signal<void (const Alert&) > OnAlert;
    typedef OnAlert::slot_type OnAlertHandler;
}

#endif	/* ALERT_H */

