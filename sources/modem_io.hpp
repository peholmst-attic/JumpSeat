#ifndef MODEM_IO_HPP
#define	MODEM_IO_HPP

#include <string>

#include "sms.hpp"
#include "phone_call.hpp"

namespace JumpSeat {

    class ModemIO {
    public:
        void addOnSMSHandler(const OnSMSHandler& handler);
        void addOnPhoneCallHandler(const OnPhoneCallHandler& handler);
        void signalFakeSms(const std::string& message);
    private:
        OnSMS smsSignal_;
        OnPhoneCall phoneCallSignal_;
    };
}

#endif	/* MODEM_IO_HPP */

