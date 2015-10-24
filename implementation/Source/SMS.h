#ifndef SMS_H
#define	SMS_H

#include <string>
#include <boost/signals2/signal.hpp>

#include "Time.h"

namespace JumpSeat {

    struct SMS {
        std::string sender;
        std::string message;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const SMS&) > OnSMS;
    typedef OnSMS::slot_type OnSMSHandler;
}

#endif	/* SMS_H */

