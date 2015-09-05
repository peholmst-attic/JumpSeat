#ifndef ALERT_DISPATCHER_HPP
#define	ALERT_DISPATCHER_HPP

#include "sms.hpp"

namespace JumpSeat
{
    class AlertDispatcher
    {
    public:
        void onReceiveSMS(const SMS& sms);        
    };
}

#endif	/* ALERT_DISPATCHER_HPP */

