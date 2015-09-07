#ifndef ALERT_LOGGER_HPP
#define	ALERT_LOGGER_HPP

#include "alert.hpp"

namespace JumpSeat
{
    class AlertLogger
    {
    public:
        void onReceiveAlert(const Alert& alert);
    };
}

#endif	/* ALERT_LOGGER_HPP */

