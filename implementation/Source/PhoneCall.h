#ifndef PHONE_CALL_H
#define	PHONE_CALL_H

#include <ctime>
#include <string>
#include <boost/signals2/signal.hpp>

#include "Time.h"

namespace JumpSeat {

    struct PhoneCall {
        std::string number;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const PhoneCall&) > OnPhoneCall;
    typedef OnPhoneCall::slot_type OnPhoneCallHandler;
}

#endif	/* PHONE_CALL_H */

