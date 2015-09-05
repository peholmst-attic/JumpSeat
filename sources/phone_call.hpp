#ifndef PHONE_CALL_HPP
#define	PHONE_CALL_HPP

#include <ctime>
#include <string>
#include <boost/signals2/signal.hpp>

namespace JumpSeat 
{

    struct PhoneCall
    {
        std::string number;
        tm timestamp;
    };
    
    typedef boost::signals2::signal<void (const PhoneCall&)> OnPhoneCall;
    typedef OnPhoneCall::slot_type OnPhoneCallHandler;
    
}

#endif	/* PHONE_CALL_HPP */

