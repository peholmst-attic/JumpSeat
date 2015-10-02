#ifndef SMS_HPP
#define	SMS_HPP

#include <string>
#include <boost/signals2/signal.hpp>

#include "time.hpp"

namespace JumpSeat {

    struct SMS {
        std::string sender;
        std::string message;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const SMS&) > OnSMS;
    typedef OnSMS::slot_type OnSMSHandler;
}

#endif	/* SMS_HPP */

