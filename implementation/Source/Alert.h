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

