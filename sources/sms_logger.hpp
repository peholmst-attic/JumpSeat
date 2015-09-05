#ifndef SMS_LOGGER_HPP
#define	SMS_LOGGER_HPP

#include "sms.hpp"

namespace JumpSeat
{
    class SMSLogger
    {
    public:
        void onReceiveSMS(const SMS& sms);
    };
}

#endif	/* SMS_LOGGER_HPP */

