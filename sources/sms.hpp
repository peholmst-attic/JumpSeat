#ifndef SMS_HPP
#define	SMS_HPP

#include <ctime>
#include <string>
#include <boost/signals2/signal.hpp>

namespace JumpSeat 
{

    struct SMS
    {
        std::string sender;
        std::string message;
        tm timestamp;
    };
    
    typedef boost::signals2::signal<void (const SMS&)> OnSMS;
    typedef OnSMS::slot_type OnSMSHandler;
    
}

#endif	/* SMS_HPP */

