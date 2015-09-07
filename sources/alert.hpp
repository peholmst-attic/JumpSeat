#ifndef ALERT_HPP
#define	ALERT_HPP

#include <ctime>
#include <string>
#include <boost/optional.hpp>
#include <boost/signals2/signal.hpp>

#include "alert_type.hpp"

namespace JumpSeat
{
    struct Alert
    {
        boost::optional<AlertType> type;
        boost::optional<std::string> municipality;
        boost::optional<std::string> address;
        std::string message;
        std::tm timestamp;
    };
    
    enum class AlertField
    {
        code,
        municipality,
        address
    };
    
    typedef boost::signals2::signal<void (const Alert&)> OnAlert;
    typedef OnAlert::slot_type OnAlertHandler;    
}

#endif	/* ALERT_HPP */

